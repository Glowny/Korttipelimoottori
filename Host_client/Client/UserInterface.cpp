#include "UserInterface.h"


UserInterface::UserInterface(sf::RenderWindow &window):_window(window)
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

	_buttonArea = (sf::FloatRect(width*0.75f,height*0.75f,
		width*0.25f,height*0.25f));

}


UserInterface::~UserInterface(void)
{

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
				std::cout << "something happens";
				for(int i = 0; i < _cardObjects.size();i++)
				{
					if(_cardObjects[i].getArea().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
						_cardObjects[i].select();
				}

				if(_buttons[0].getArea().contains(sf::Vector2f(sf::Mouse::getPosition(_window))))
				{
					std::cout << "plaaksd";
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
	removeCards(tempHand);
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
		_buttons[i].setPosition(sf::Vector2f(_buttonArea.left+width*0.5f,_buttonArea.top+i*height));
	}
}

void UserInterface::draw()
{
	for(int i = 0; i < _cardObjects.size(); i++)
	{
		_cardObjects[i].draw(_window);
	}
	for(int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].draw(_window);
	}
}