#include "DeckMenu.h"


DeckMenu::DeckMenu(AssetLoader &al,sf::Vector2u windowsize):ToolMenu(al, windowsize)
{
	area.setPosition(windowsize.x*0.8f,0);
	area.setSize(sf::Vector2f(windowsize.x*0.2f,windowsize.y));
	buttons.clear();
	buttons.push_back(ButtonObject(font,"Make Deck"));
	buttons.push_back(ButtonObject(font,"Up Deck"));
	buttons.push_back(ButtonObject(font,"Delete Deck"));

	loadDecks();
	arrange(buttons,0);
	showDecks = false;
}

void DeckMenu::newDeckOption(std::string name)
{
	
}

int DeckMenu::checkButtons(sf::Vector2i mousepos)
{
	int pushed = -1;

	for(int i = 0; i < buttons.size(); i++)
	{
		if(buttons[i].getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			buttons[i].flash();
			pushed = i;
			break;
		}
	}
	
	if(showDecks)
	{
	for(int i = 0; i < secondButtons.size(); i++)
	{
		if(secondButtons[i].getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			pushed = buttons.size()+i;
			break;
		}
	}
	}
	
	return pushed;
}

void DeckMenu::loadDecks()
{
	secondButtons.clear();

	for(int i = 0; i < assLoad.getDecks().size();i++)
	{	
		secondButtons.push_back(ButtonObject(font,assLoad.getDecks()[i].toString()));
	}
	arrange(secondButtons,-area.getSize().x);

	for(int i = 0; i < secondButtons.size();i++)
	{
		secondButtons[i].adapt();
	}
}

void DeckMenu::draw(sf::RenderWindow &window)
{

	window.draw(area);

	for(int i = 0; i < buttons.size();i++)
	{
		buttons[i].draw(window);
	}
	
	if(showDecks)
	{
	for(int i = 0; i < secondButtons.size();i++)
	{
		secondButtons[i].draw(window);
	}
	}
}

DeckMenu::~DeckMenu(void)
{
}
