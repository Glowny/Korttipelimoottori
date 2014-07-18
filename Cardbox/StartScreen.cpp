#include "StartScreen.h"


StartScreen::StartScreen(AssetLoader &al) :assLoad(al), _window(sf::RenderWindow(sf::VideoMode(512,256,32),"NextCardGame"))
{	
	
	sf::Vector2u size(_window.getSize());
	_textInput.setPosition(size.x*0.5f,size.y*0.75f);
	_screenText.setPosition(size.x*0.5f,size.y*0.25f);
	_blockText.setPosition(size.x*0.5f,size.y*0.5f);

	_textInput.setColor(sf::Color::Green);
	_screenText.setColor(sf::Color::White);

	_font = *assLoad.getFont();
	_textInput.setCharacterSize(24);
	_screenText.setCharacterSize(32);
	_blockText.setCharacterSize(40);

	_textInput.setFont(_font);
	_screenText.setFont(_font);
	_blockText.setFont(_font);

	_LeftBlock = sf::RectangleShape(sf::Vector2f(size.x*0.3333f,size.y*0.5f));
	_CenterBlock = sf::RectangleShape(sf::Vector2f(size.x*0.3333f,size.y*0.5f));
	_RightBlock = sf::RectangleShape(sf::Vector2f(size.x*0.3333f,size.y*0.5f));

	_LeftBlock.setPosition(sf::Vector2f(0,size.y*0.5f));
	_CenterBlock.setPosition(sf::Vector2f(size.x*0.3333f,size.y*0.5f));
	_RightBlock.setPosition(sf::Vector2f(size.x*0.6666f,size.y*0.5f));

	sf::Mouse::setPosition(sf::Vector2i((_window.getPosition().x+_window.getSize().x*0.5f),(_window.getPosition().y+_window.getSize().y*0.5f)));
	_option = PLAY;
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

void StartScreen::askWhatYouWannaDo()
{
	sf::Event Event;

		_screenText.setString("WhatYouWannaDo?");
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

				if(Event.key.code == sf::Keyboard::Left)
				{
					if(_option != HOSTPLAY)
						_option--;
					else
						_option = HOST;
				}
				if(Event.key.code == sf::Keyboard::Right)
				{

					if(_option != HOST)
						_option++;
					else
						_option = HOSTPLAY;
				}

				if(Event.key.code == sf::Keyboard::Return)
				{

				_LeftBlock.setFillColor(sf::Color::Transparent);
				_CenterBlock.setFillColor(sf::Color::Transparent);
				_RightBlock.setFillColor(sf::Color::Transparent);
				_blockText.setString("");
					switch(_option)
					{
					case HOSTPLAY:
						askID();
						done = true;
						break;
					case PLAY:
						askID();
						askIP();
						done = true;
						break;

					case HOST:
						done = true;
						break;

					}
				}

		switch(_option)
			{
			case HOSTPLAY:
				_LeftBlock.setFillColor(sf::Color::Green);
				_CenterBlock.setFillColor(sf::Color::White);
				_RightBlock.setFillColor(sf::Color::White);
				_blockText.setPosition(_LeftBlock.getPosition());
				_blockText.setString("HOSTPLAY");
				break;
			case PLAY:
				_LeftBlock.setFillColor(sf::Color::White);
				_CenterBlock.setFillColor(sf::Color::Green);
				_RightBlock.setFillColor(sf::Color::White);
				_blockText.setPosition(_CenterBlock.getPosition());
				_blockText.setString("PLAY");
				break;
			case HOST:
				_CenterBlock.setFillColor(sf::Color::White);
				_RightBlock.setFillColor(sf::Color::Green);
				_LeftBlock.setFillColor(sf::Color::White);
				_blockText.setPosition(_RightBlock.getPosition());
					_blockText.setString("HOST");
				break;
			}

			}
		}
		draw();
		}



}

void StartScreen::run()
{
	askWhatYouWannaDo();
	_window.close();
}


void StartScreen::draw()
{	
	_window.draw(_LeftBlock);
	_window.draw(_CenterBlock);
	_window.draw(_RightBlock);

	_window.draw(_textInput);
	_window.draw(_screenText);
	_window.draw(_blockText);

	_window.display();
	_window.clear();

}


StartScreen::~StartScreen(void)
{
}
