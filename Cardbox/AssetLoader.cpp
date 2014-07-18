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
	std::ifstream ipFile("AssetList.txt");
	std::string texture;
	if(ipFile)
	{
		while(std::getline(ipFile,texture))
		{
			sf::Texture *temp = new sf::Texture;
			std::map<std::string,sf::Texture*>::iterator it;
			it = textureMap.begin();
			temp->loadFromFile(texture);
			textureMap.insert(it,make_pair(texture,temp));
		}

		ipFile.close();
	}

}

void AssetLoader::writeAssetList()
{
	std::ofstream opFile("AssetList.txt",std::ios::trunc);

	if(opFile)
	{

		std::map<std::string,sf::Texture*>::iterator it;
		it = textureMap.begin();
		
		while(it != textureMap.end())
		{
			opFile << it->first <<"\n";
			it++;
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

void AssetLoader::newImage(std::string s)
{
	sf::Texture *temp = new sf::Texture;
	temp->loadFromFile(s);

	std::map<std::string,sf::Texture*>::iterator it;
	it = textureMap.begin();
	textureMap.insert(it,std::make_pair(s,temp));

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