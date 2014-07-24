#pragma once
#include "SFML\Graphics.hpp"
#include "Deck.h"
#include <map>
#include <fstream>

class AssetLoader
{
public:
	AssetLoader(void);
	~AssetLoader(void);
	sf::Font* getFont();
	sf::Texture* getTexture(std::string s);
	void newDeck(std::string s,int amount,int sizex,int sizey);
	void eraseDeck(std::string s,int amount, int sizex, int sizey);
	bool check(std::string s);
	std::vector<Deck> getDecks(){return deckVector;};
private:
	std::map<std::string,sf::Texture*>textureMap;
	std::vector<Deck>deckVector;
	sf::Font *font;
	void readAssetList();
	void writeAssetList();
};

