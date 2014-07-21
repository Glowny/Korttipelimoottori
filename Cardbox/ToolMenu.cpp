#include "ToolMenu.h"


ToolMenu::ToolMenu(AssetLoader &al,sf::Vector2u windowSize):assLoad(al)
{
	font = *assLoad.getFont();
	area = sf::RectangleShape(sf::Vector2f(windowSize.x*0.33f,windowSize.y));
	area.setPosition(windowSize.x,0);
	buttons.push_back(ButtonObject(font,"Make Area"));
	buttons.push_back(ButtonObject(font,"Exit"));
	buttons[0].setSize(sf::Vector2f(area.getSize().x, area.getSize().y*0.1));
	buttons[0].setPosition(sf::Vector2f(area.getGlobalBounds().left,0));
	buttons[1].setSize(sf::Vector2f(area.getSize().x, area.getSize().y*0.1));
	buttons[1].setPosition(sf::Vector2f(area.getGlobalBounds().left,area.getSize().y*0.1));
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
			pushed = i;
			break;
		}
	}
	return pushed;
}




ToolMenu::~ToolMenu(void)
{
}
