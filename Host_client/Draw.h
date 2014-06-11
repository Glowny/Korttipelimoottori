#pragma once
#include "Kortti.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Draw
{
public:
	Draw(std::vector<Kortti> *k, sf::RenderWindow *w, Kortti *tc, Kortti *cc, sf::Vector2f cS);	// pointterileikkejä jotta pysyy päivitys ajan tasalla
	~Draw(void);
	void drawLoop();
	void drawHand();
	void drawTopC();
	void drawCurrentC();
	void drawOtherP();
	sf::IntRect getRectPos(int s);
private:
	sf::Vector2f cardSize;
	std::vector<Kortti> *Hand;
	sf::RenderWindow *clientWindow;
	Kortti *topCard;
	Kortti *currentCard;
	sf::Texture hearts;
	sf::Texture diamonds;
	sf::Texture clubs;
	sf::Texture spades;
	sf::Texture suits;
	sf::Font font;

};

