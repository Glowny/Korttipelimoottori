#pragma once
#include "SFML\Graphics.hpp"
class MouseExplosion 
{
public:
	MouseExplosion(sf::Vector2f pos,sf::Color color1,sf::Color color2);
	bool update();
	void checkWindowCollision(sf::RenderWindow &window);
	~MouseExplosion(void);
	void setNewSpeed(sf::Vector2f speed,int index){_speeds[index] = speed;}
	int getParticleAmount(){return _particles.getVertexCount();}
	void draw(sf::RenderWindow &window);

private:
	sf::Clock _timer2;
	sf::Clock _timer;
	sf::VertexArray _particles;
	std::vector<sf::Vector2f>_speeds;
	sf::Clock _timer3;
	int trigger;
};