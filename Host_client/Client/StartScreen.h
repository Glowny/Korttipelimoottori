#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include<string>

class StartScreen
{
public:
	StartScreen();
	~StartScreen(void);
	void run();
	sf::IpAddress getIp(){sf::IpAddress _ip(_ipString); return _ip;}
	std::string getID(){return _id;}

private:
	void askID();
	void askIP();
	void draw();
	sf::Font _font;
	sf::Text _textInput;
	sf::Text _screenText;
	std::string _id, _ipString;
	sf::RenderWindow _window;
	
};

