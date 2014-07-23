#include "DeckMaker.h"


DeckMaker::DeckMaker(AssetLoader &al):assLoad(al),_window(sf::RenderWindow(sf::VideoMode(500,200,32),"DeckMaker"))
{
	_window.setActive(false);
	_window.setVisible(false);

	sf::Vector2u size(_window.getSize());
	_textInput.setPosition(size.x*0.5f,size.y*0.75f);
	_screenText.setPosition(size.x*0.5f,size.y*0.25f);

	_textInput.setColor(sf::Color::Green);
	_screenText.setColor(sf::Color::White);

	_font = *assLoad.getFont();
	_textInput.setCharacterSize(24);
	_screenText.setCharacterSize(32);

	_textInput.setFont(_font);
	_screenText.setFont(_font);
	
}

std::string DeckMaker::askString(std::string question)
{
	
	sf::Event Event;

	_screenText.setString(question);
	_screenText.setOrigin(_screenText.getGlobalBounds().width*0.5f,_screenText.getGlobalBounds().height*0.5f);
	bool done = false;
	while(!done)
	{
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
				else if(Event.key.code == sf::Keyboard::Return)
				{	
					if(_stringInput!="")
					{
						done = true;
					}
				}
				else if(Event.key.code == sf::Keyboard::BackSpace)
				{
					if(_stringInput!= "")
					_stringInput.erase(_stringInput.end()-1);
				}
				break;
			case sf::Event::TextEntered:
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				_stringInput += Event.text.unicode;
				break;
			}
			_textInput.setString(_stringInput);
			_textInput.setOrigin(_textInput.getGlobalBounds().width*0.5f,_textInput.getGlobalBounds().height*0.5f);
			draw();

		}
	}

	return _stringInput;

}

int DeckMaker::askInt(std::string question)
{
	
	sf::Event Event;

	_stringInput.clear();
	_textInput.setString("");
	_screenText.setString(question);
	_screenText.setOrigin(_screenText.getGlobalBounds().width*0.5f,_screenText.getGlobalBounds().height*0.5f);
	bool done = false;
	while(!done)
	{
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
				else if(Event.key.code == sf::Keyboard::Return)
				{	
					if(_stringInput!="")
					{
						done = true;
					}
				}
				else if(Event.key.code == sf::Keyboard::BackSpace)
				{
					if(_stringInput!= "")
					_stringInput.erase(_stringInput.end()-1);
				}
				break;
			case sf::Event::TextEntered:
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				_stringInput += Event.text.unicode;
				break;
			}
			_textInput.setString(_stringInput);
			_textInput.setOrigin(_textInput.getGlobalBounds().width*0.5f,_textInput.getGlobalBounds().height*0.5f);
			draw();

		}
	}

	int completeInt = 0;
	int intBuffer;
	char charBuffer;
	int stringSize = _stringInput.size();
	float power = 0;
	float base = 10;

		
	for(int i = 0; i < stringSize;i++)
	{
		charBuffer = _stringInput.at(i);

		intBuffer = (int)charBuffer - '0';


		power = pow(base,(stringSize-1-i));
	
		intBuffer*=power;
		

		completeInt+=intBuffer;
	}

	return completeInt;

}


void DeckMaker::run()
{
	_window.setActive(true);
	_window.setVisible(true);

	std::string filename;
	int amount,width,height;
	filename = askString("Enter Filename");
	amount = askInt("Enter Card amount");
	width = askInt("Enter Card width");
	height = askInt("Enter Card height");

	std::cout<<filename<<" "<<amount<<" "<<width<<" "<<height<<std::endl;

	assLoad.newDeck(filename,amount,width,height);

	_window.setActive(false);
	_window.setVisible(false);
}

void DeckMaker::draw()
{
	_window.draw(_textInput);
	_window.draw(_screenText);

	_window.display();
	_window.clear();

}
DeckMaker::~DeckMaker(void)
{
}
