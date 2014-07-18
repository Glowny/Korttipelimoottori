#include "ToolMenu.h"


ToolMenu::ToolMenu(AssetLoader &al,sf::Vector2u windowSize):assLoad(al)
{
	font = *assLoad.getFont();
	area = sf::RectangleShape(sf::Vector2f(windowSize.x*0.33f,windowSize.y));
	area.setPosition(windowSize.x,0);
	buttons.push_back(ButtonObject(font,"diipadaapa"));
	buttons[0].setPosition(sf::Vector2f(area.getGlobalBounds().left+area.getSize().x*0.5f,0));
}

void ToolMenu::draw(sf::RenderWindow &window)
{
	window.draw(area);

	for(int i = 0;i < buttons.size();i++)
	{
		buttons[i].draw(window);
	}
}


ToolMenu::~ToolMenu(void)
{
}
