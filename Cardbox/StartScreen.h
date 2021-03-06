#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include<string>
#include "AssetLoader.h"

enum OPTION{
	HOSTPLAY,
	PLAY,
	HOST
};

class StartScreen
{
public:
	StartScreen(AssetLoader &al);
	~StartScreen(void);
	void run();
	sf::IpAddress getIp(){sf::IpAddress _ip(_ipString); return _ip;}
	std::string getID(){return _id;}
	int getOption(){return _option;}

private:
	AssetLoader &assLoad;
	void askWhatYouWannaDo();
	void askID();
	void askIP();
	void draw();
	sf::Font _font;
	sf::Text _textInput;
	sf::Text _screenText;
	sf::Text _blockText;
	std::string _id, _ipString;
	sf::RenderWindow _window;
	int _option;
	sf::RectangleShape _LeftBlock;
	sf::RectangleShape _CenterBlock;
	sf::RectangleShape _RightBlock;
	
};