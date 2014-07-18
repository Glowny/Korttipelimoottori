#pragma once
#include "SFML\Graphics.hpp"
#include <map>
#include <fstream>

class AssetLoader
{
public:
	AssetLoader(void);
	~AssetLoader(void);
	sf::Font* getFont();
	sf::Texture* getTexture(std::string s);
	void newImage(std::string s);
	bool check(std::string s);
private:
	std::map<std::string,sf::Texture*>textureMap;
	sf::Font *font;
	void readAssetList();
	void writeAssetList();
};

