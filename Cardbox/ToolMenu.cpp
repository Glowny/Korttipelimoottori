#include "ToolMenu.h"


ToolMenu::ToolMenu(AssetLoader &al,sf::Vector2u windowSize):assLoad(al)
{
	font = *assLoad.getFont();
	area = sf::RectangleShape(sf::Vector2f(windowSize.x*0.2f,windowSize.y));
	area.setPosition(windowSize.x,0);
	buttons.push_back(ButtonObject(font,"Make Area"));
	buttons.push_back(ButtonObject(font,"Deckings"));
	buttons.push_back(ButtonObject(font,"Exit"));
	
	arrange(buttons,0);


}

void ToolMenu::arrange(std::vector<ButtonObject>&butts, int placement)
{
	for(int i = 0; i <butts.size();i++)
	{
		butts[i].setSize(sf::Vector2f(area.getSize().x, area.getSize().y*0.075f));
		butts[i].setPosition(sf::Vector2f(area.getGlobalBounds().left+placement,i*area.getSize().y*0.075f));
	}
}

void ToolMenu::draw(sf::RenderWindow &window)
{
	window.draw(area);

	for(int i = 0;i < buttons.size();i++)
	{
		buttons[i].draw(window);
	}
}

int ToolMenu::checkButtons(sf::Vector2i mousePos)
{
	int pushed = -1;

	for(int i = 0; i < buttons.size(); i++)
	{
		if(buttons[i].getGlobalBounds().contains(sf::Vector2f(mousePos)))
		{
			buttons[i].flash();
			pushed = i;
			break;
		}
	}
	return pushed;
}




ToolMenu::~ToolMenu(void)
{
}
