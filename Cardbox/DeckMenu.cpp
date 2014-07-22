#include "DeckMenu.h"


DeckMenu::DeckMenu(AssetLoader &al,sf::Vector2u windowsize):ToolMenu(al, windowsize)
{
	area.setPosition(windowsize.x*0.5f,0);
	buttons.clear();
	buttons.push_back(ButtonObject(font,"Make Deck"));
	buttons.push_back(ButtonObject(font,"Up Deck"));

	for(int i = 0; i <buttons.size();i++)
	{
		buttons[i].setSize(sf::Vector2f(area.getSize().x, area.getSize().y*0.1));
		buttons[i].setPosition(sf::Vector2f(area.getGlobalBounds().left,i*area.getSize().y*0.1));
	}

}


DeckMenu::~DeckMenu(void)
{
}
