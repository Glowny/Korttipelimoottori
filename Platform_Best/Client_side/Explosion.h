#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
class Explosion
{
public:
	Explosion(sf::Vector2f pos);
	~Explosion(void);
	bool update();
	void draw(sf::RenderWindow &window);
private:
	bool trigger;
	sf::Clock _timer2;
	sf::Clock _timer;
	sf::VertexArray _particles;
	std::vector<sf::Vector2f>_speeds;
};

