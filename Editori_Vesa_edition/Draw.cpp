#include "Draw.h"


Draw::Draw(std::vector<sf::RectangleShape*> &sV, sf::RenderWindow &w, std::vector<MouseExplosion>&explosions) : window(w), shapeVector(sV), _explosions(explosions)
{

}


Draw::~Draw(void)
{
}

void Draw::DrawStuff()
{
	for(int i = 0; i <shapeVector.size(); i++)
	{
		window.draw(*shapeVector[i]);
		
	}
	for(int i = 0; i < _explosions.size(); i++)
		{
			_explosions[i].draw(window);
		}
}