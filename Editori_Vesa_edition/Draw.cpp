#include "Draw.h"


Draw::Draw(std::vector<Shape*> &sV, sf::RenderWindow &w, std::vector<MouseExplosion>&explosions) : window(w), shapeVector(sV), _explosions(explosions)
{
	font.loadFromFile("comic.ttf");
	text.setFont(font);
	text.setCharacterSize(40);
}


Draw::~Draw(void)
{
}
void Draw::DrawTop(std::vector<sf::RectangleShape> s,std::vector<int> i)
{
	std::vector<sf::RectangleShape> topVector = s;
	for (int j = 0; j < topVector.size(); j++)
	{
		window.draw(topVector[j]);
		DrawTextNumber("",i[j],topVector[j].getPosition());
	}
}
void Draw::DrawTop(std::vector<sf::RectangleShape> s)
{
	std::vector<sf::RectangleShape> topVector = s;
	for (int i = 0; i < topVector.size(); i++)
	{
		window.draw(topVector[i]);
	}
}
void Draw::DrawTextNumber(std::string s,float n, sf::Vector2f pos)
{
	n = n*2;
	std::ostringstream convert;
	std::string result;
	convert <<n;
	result = convert.str();
	result = s + result;
	sf::Text text(result, font);
	text.setCharacterSize(30);
	text.setPosition(pos);
	window.draw(text);
}
void Draw::DrawTextNumber(std::string s,int n, sf::Vector2f pos)
{
	std::ostringstream convert;
	std::string result;
	convert <<n;
	result = convert.str();
	result = s + result;
	sf::Text text(result, font);
	text.setCharacterSize(30);
	text.setPosition(pos);
	window.draw(text);
}
void Draw::DrawStuff()
{
	for(int i = 0; i <shapeVector.size(); i++)
	{
		window.draw(shapeVector[i]->rect);
			if(shapeVector[i]->type == 2)
		{

			sf::Vector2f position = shapeVector[i]->rect.getPosition();
			sf::Vector2f sizes = shapeVector[i]->rect.getSize();
			std::ostringstream convert;
			std::string result;
			if (shapeVector[i]->number > 9)
			{
				text.setCharacterSize(40);
			}
			else if (shapeVector[i]->number > 99)
			{
				text.setCharacterSize(30);
			}
			else
			{
				text.setCharacterSize(40);
			}
			convert << shapeVector[i]->number;
			result = convert.str();
			text.setString(result);
			text.setPosition(position);
			window.draw(text);
			sf::RectangleShape rect(sizes);

			text.setCharacterSize(60);
			rect.setPosition(position.x+sizes.x,position.y);
			rect.setFillColor(sf::Color::Magenta);
			window.draw(rect);
			text.setString("+");
			text.setPosition(rect.getPosition());
			window.draw(text);
			
			rect.setPosition(position.x-sizes.x,position.y);
			window.draw(rect);
			text.setString("-");
			text.setPosition(rect.getPosition());
			window.draw(text);

			rect.setFillColor(sf::Color::Green);
			rect.setPosition(position.x,position.y+sizes.y);
			window.draw(rect);
			text.setCharacterSize(30);
			text.setString("set");
			text.setPosition(rect.getPosition());
			window.draw(text);
			text.setCharacterSize(50);
		}
	}
	for(int i = 0; i < _explosions.size(); i++)
		{
			_explosions[i].draw(window);
		}
}