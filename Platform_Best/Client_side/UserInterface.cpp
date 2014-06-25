#include "UserInterface.h"
#include "chekkeri.h"

UserInterface::UserInterface(sf::RenderWindow &window, Table &table):_window(window), _table(table)
{
	_cardFont = new sf::Font;
	float width = _window.getSize().x;
	float height = _window.getSize().y;
	_suitTexture = new sf::Texture;
	if((*_suitTexture).loadFromFile("suits_tilemap.png"))
	std::cout << "suits loaded succesfully" << std::endl;
	_cardFont->loadFromFile("comic.ttf");
	_cardArea = (sf::FloatRect(0,height*0.75f,
		width*0.75f,height*0.25f));
	_selectedArea = NOTHING;

	_buttonArea = (sf::FloatRect(width*0.75f,height*0.75f,
		width*0.25f,height*0.25f));

}


UserInterface::~UserInterface(void)
{

}

void UserInterface::init(std::vector<sf::FloatRect> areas)
{
	for(int i = 0; i < areas.size();i++)
	{
	_borders.push_back(sf::RectangleShape(sf::Vector2f(areas[i].width,areas[i].height)));
	_borders[i].setFillColor(sf::Color::Transparent);
	_borders[i].setOutlineThickness(1.0f);
	_borders[i].setPosition(areas[i].left,areas[i].top);
	}
}

bool UserInterface::checkInput()
{

	bool ready = false;
	sf::Event Event;
	while(_window.pollEvent(Event))
	{
		switch(Event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::KeyPressed:
			if(Event.key.code == sf::Keyboard::Escape)
				_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(_borders[0].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
				{
					_borders[1].setFillColor(sf::Color::Transparent);
					_borders[0].setFillColor(sf::Color(50,50,50,50));
					_selectedArea = TABLE_CENTER;
				}

				if(_borders[1].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
				{
					_borders[0].setFillColor(sf::Color::Transparent);
					_borders[1].setFillColor(sf::Color(50,50,50,50));
					_selectedArea = SECONDARY_CARDS;
				}

				std::cout << "something happens";

				for(int i = 0; i < _cardObjects.size();i++)
				{
					if(_cardObjects[i].getArea().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
					{
						if(check(Card(_cardObjects[i].value, _cardObjects[i].suit),_cards,_table))
							_cardObjects[i].select();
					}
				}

				if(_buttons[0].getArea().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
				{
					if(_selectedArea == NOTHING)
						_popUps.push_back(PopUp(*_cardFont,"Select Area!", sf::Vector2f(_window.getSize().x*0.5f, _window.getSize().y*0.5f),sf::Vector2f(150,50),1));
					else
						ready = true;
				}
			}
			break;
			
		}
	}
	return ready;
}

void UserInterface::removeCards(Hand cards)
{
	bool erased;

	for(int i = 0; i < _cardObjects.size();)
	{
		erased = false;
		for(int j = 0; j < cards.hand.size();j++)
		{
			if(cards.hand[j] == _cardObjects[i])
			{
				std::cout << "Deleted: " << _cardObjects[i].suit << std::endl
						<<	_cardObjects[i].value << std::endl;
				_cardObjects.erase(_cardObjects.begin()+i);
				_cards.hand.erase(_cards.hand.begin()+i);
				erased = true;
			}
		}
		if(!erased)
			i++;
	}
	lineUpCards();
}

void UserInterface::addCards(Hand cards)
{
	for(int i = 0; i < cards.hand.size();i++)
	{
		_cardObjects.push_back(CardObject(cards.hand[i],*_suitTexture,*_cardFont));
		_cards.hand.push_back(cards.hand[i]);
	}
	for(int i = 0; i < _cardObjects.size(); i++)
	{
		_cardObjects[i].setSize(sf::Vector2f(_cardArea.height*0.5f,_cardArea.height));
	}
	lineUpCards();
}

Hand UserInterface::getSelected()
{

	Hand tempHand;

	for(int i = 0; i < _cardObjects.size();i++)
	{
		if(_cardObjects[i]._selected)
		{
			tempHand.add(Card(_cardObjects[i].value,_cardObjects[i].suit));
		}
	}
	return tempHand;
}

void UserInterface::lineUpCards()
{
	float width = _cardArea.width;
	float height = _cardArea.height;

	if(_cardObjects.size()>0)
	width/=_cardObjects.size();

	for(int i = 0; i < _cardObjects.size();i++)
	{
		_cardObjects[i].setPosition(sf::Vector2f(_cardArea.left+i*width,_cardArea.top));
	}
}

void UserInterface::addButton(std::string string)
{
	_buttons.push_back(ButtonObject(*_cardFont, string));
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].setSize(sf::Vector2f(_buttonArea.width,_buttonArea.height*0.2f));
	}
	lineUpButtons();
}
void UserInterface::addButton(std::string string, sf::Texture texture)
{
	_buttons.push_back(ButtonObject(*_cardFont, string, texture));
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].setSize(sf::Vector2f(_buttonArea.width,_buttonArea.height*0.2f));
	}
	lineUpButtons();
}

void UserInterface::lineUpButtons()
{
	float height = _buttonArea.height;
	float width = _buttonArea.width;

	if(_buttons.size()>0)
		height/=_buttons.size();

	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].setPosition(sf::Vector2f(_buttonArea.left,_buttonArea.top+i*height));
	}
}

void UserInterface::endScreen(std::string player,std::string message,bool victory)
{

	std::string temp;

	if(victory)
	{
		temp = "YOU WIN THE GAME!";
		_popUps.push_back(PopUp(*_cardFont,temp,sf::Vector2f(_window.getSize().x*0.5f-100,_window.getSize().y*0.5f-50),sf::Vector2f(200,100),60));
	}

	else
	{
		temp = player;
	 	temp+=" WINS THE GAME!";
		_popUps.push_back(PopUp(*_cardFont,temp,sf::Vector2f(_window.getSize().x*0.5f-100,_window.getSize().y*0.5f-50),sf::Vector2f(200,100),60));
	}

	temp = message;
	
	std::cout<<temp<<std::endl;

	_popUps.push_back(PopUp(*_cardFont,temp,sf::Vector2f(_window.getSize().x*0.5-100,_window.getSize().y-105),sf::Vector2f(200,100),60));
}

void UserInterface::draw()
{
	for(int i = 0;i < _borders.size();i++)
	{
		_window.draw(_borders[i]);
	}

	for(int i = 0; i < _cardObjects.size(); i++)
	{
		_cardObjects[i].draw(_window);
	}
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].draw(_window);
	}

	for(int i = 0; i <_popUps.size(); i++)
	{
		if(_popUps[i].draw(_window))
			_popUps.erase(_popUps.begin()+i);
	}
}