#pragma once
#include "Kortti.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Draw
{
public:
	Draw(std::vector<Kortti> *k, sf::RenderWindow *w);	// pointterileikkejä jotta pysyy päivitys ajan tasalla
	~Draw(void);
	void drawLoop();
private:
	std::vector<Kortti> *Hand;
	sf::RenderWindow *clientWindow;
	sf::Texture hearts;
	sf::Texture diamonds;
	sf::Texture clubs;
	sf::Texture spades;

};

