#include "StartScreen.h"


StartScreen::StartScreen(void) : _window(sf::RenderWindow(sf::VideoMode(512,256,32),"NextCardGame"))
{	
	
	sf::Vector2u size(_window.getSize());
	_textInput.setPosition(size.x*0.5f,size.y*0.75f);
	_screenText.setPosition(size.x*0.5f,size.y*0.25f);
	_textInput.setColor(sf::Color::Green);
	_screenText.setColor(sf::Color::White);
	_font.loadFromFile("comic.ttf");
	_textInput.setCharacterSize(24);
	_screenText.setCharacterSize(32);
	_textInput.setFont(_font);
	_screenText.setFont(_font);
	sf::Mouse::setPosition(sf::Vector2i((_window.getPosition().x+_window.getSize().x*0.5f),(_window.getPosition().y+_window.getSize().y*0.5f)));
}

void StartScreen::askID()
{
		sf::Event Event;

		_screenText.setString("Enter Identification please: ");
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
						if(_id!="")
						{
							done = true;
						}
					}
					else if(Event.key.code == sf::Keyboard::BackSpace)
					{
						if(_id != "")
						_id.erase(_id.end()-1);
					}
					break;
				case sf::Event::TextEntered:
					if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
					_id += Event.text.unicode;
					break;
				}
				_textInput.setString(_id);
				_textInput.setOrigin(_textInput.getGlobalBounds().width*0.5f,_textInput.getGlobalBounds().height*0.5f);
				draw();

			}
		}

}

void StartScreen::askIP()
{
	sf::Event Event;

		_screenText.setString("Enter IP please: ");
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
					if(_ipString!="")
					{
						done = true;
					}
				}
				else if(Event.key.code == sf::Keyboard::BackSpace)
				{
					if(_ipString != "")
					_ipString.erase(_ipString.end()-1);
				}
				else if(Event.key.code == sf::Keyboard::Down)
				{
					_ipString = sf::IpAddress::getLocalAddress().toString();
				}
				break;
				
			case sf::Event::TextEntered:
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
					_ipString += Event.text.unicode;
				break;
			}
			_textInput.setString(_ipString);
			_textInput.setOrigin(_textInput.getGlobalBounds().width*0.5f,_textInput.getGlobalBounds().height*0.5f);
			draw();

		}
		}

}

void StartScreen::run()
{
	askID();
	askIP();
	_window.close();
}


void StartScreen::draw()
{	
	_window.draw(_textInput);
	_window.draw(_screenText);
	_window.display();
	_window.clear();

}


StartScreen::~StartScreen(void)
{
}
