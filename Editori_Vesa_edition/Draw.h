#pragma once
#include "Shape.h"
#include <SFML\Graphics.hpp>
#include "MouseExplosion.h"
#include <vector>
#include <sstream> 
class Draw
{
public:
	Draw(std::vector<Shape*>&sV, sf::RenderWindow &w, std::vector<MouseExplosion>&explosions);
	~Draw(void);
	void DrawStuff();
	void Draw::DrawTop(std::vector<sf::RectangleShape> s,std::vector<int> i);
	void Draw::DrawTop(std::vector<sf::RectangleShape> s);
	void Draw::DrawTextNumber(std::string s, float n, sf::Vector2f pos);
	void Draw::DrawTextNumber(std::string s,int n, sf::Vector2f pos);
private:
	std::vector<Shape*> &shapeVector;
	sf::RenderWindow &window;
	std::vector<MouseExplosion>&_explosions;
	sf::Font font;
	sf::Text text;
};

