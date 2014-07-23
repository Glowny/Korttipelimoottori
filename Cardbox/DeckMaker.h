#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include "AssetLoader.h"
#include "Deck.h"
#include <iostream>
#include <math.h>

class DeckMaker
{
public:
	DeckMaker(AssetLoader &al);
	~DeckMaker(void);
	void run();
	void draw();
	std::string askString(std::string question);
	int askInt(std::string question);
	Deck newDeck();
private:
	sf::RenderWindow _window;
	sf::Text _screenText;
	sf::Text _textInput;
	std::string _stringInput;
	sf::Font _font;
	AssetLoader &assLoad;
};

