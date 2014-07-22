#include "AssetLoader.h"


AssetLoader::AssetLoader(void)
{
	font = new sf::Font;
	font->loadFromFile("comic.ttf");
	readAssetList();
}



AssetLoader::~AssetLoader(void)
{

}

void AssetLoader::readAssetList()
{
	std::fstream ipFile("DeckList.dat",std::ios::binary|std::ios::in);
	std::string texture;
	if(ipFile)
	{
		while(ipFile.peek() != EOF)
		{
			Deck tempDeck;
			tempDeck.readFromFile(ipFile);

			deckVector.push_back(tempDeck);

			sf::Texture *temp = new sf::Texture;
			std::map<std::string,sf::Texture*>::iterator it;
			it = textureMap.begin();
			temp->loadFromFile(tempDeck.getName());
			textureMap.insert(it,make_pair(tempDeck.getName(),temp));	
		}

		ipFile.close();
	}

}

void AssetLoader::writeAssetList()
{
	std::fstream opFile("DeckList.dat",std::ios::trunc|std::ios::binary|std::ios::out);

	if(opFile)
	{

		for(int i = 0; i < deckVector.size();i++)
		{
			deckVector[i].writeToFile(opFile);
		}

		opFile.close();
	}
}

sf::Font* AssetLoader::getFont()
{	
	return font;
}

sf::Texture* AssetLoader::getTexture(std::string s)
{
	std::map<std::string,sf::Texture*>::iterator it;

	it = textureMap.find(s);
	
	if(it!=textureMap.end())
		return	it->second;
	else
		return NULL;
}

void AssetLoader::newDeck(std::string s,int amount,int sizex,int sizey)
{
	sf::Texture *temp = new sf::Texture;
	temp->loadFromFile(s);

	std::map<std::string,sf::Texture*>::iterator it;
	it = textureMap.begin();
	textureMap.insert(it,std::make_pair(s,temp));
	deckVector.push_back(Deck(s,amount,sizex,sizey));

	writeAssetList();
}

bool AssetLoader::check(std::string s)
{
	std::map<std::string,sf::Texture*>::iterator it;
	for(it = textureMap.begin(); it != textureMap.end(); it++)
	{
		if(it->first == s)
			return true;
	}
	return false;
}