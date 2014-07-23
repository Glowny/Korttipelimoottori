#pragma once
#include "ToolMenu.h"


class DeckMenu : public ToolMenu
{
public:
	DeckMenu(AssetLoader &al,sf::Vector2u windowsize);
	void draw(sf::RenderWindow &window);
	int checkButtons(sf::Vector2i mousePos);
	void upDecks(){showDecks = !showDecks;}
	void loadDecks();
	~DeckMenu(void);
private:
	
	void newDeckOption(std::string name);
	std::vector<ButtonObject>secondButtons;
	bool showDecks;
	
};

