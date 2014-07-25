#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "CardInfo.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
class Editor
{
public:
	Editor(void);
	~Editor(void);
	void run();
	void save();
	void resizeImage(float newSize);
	void setImage(std::string fileName);
	void draw();
	void setGrid();
	void setGridAmount(sf::Vector2i amount);
	void setGridSize(sf::Vector2f size);
	void buttonActions();
	bool checkCoords(sf::Vector2f coords);
	int getIndexCoords();

private:
	std::vector<int> cardAmounts;
	sf::RenderWindow window;
	sf::Vector2f mousePos;
	sf::RectangleShape picture;
	sf::Texture pictureTexture;
	sf::Vector2i gridAmount;
	sf::Vector2f gridSize;
	std::vector<sf::RectangleShape> buttons;
	std::vector<sf::VertexArray> grid;
	bool mousePressed;
	sf::Font font;
	sf::Text text;
	std::string input;
	bool inputOn;
	int inputTarget;
	int oldInputSize;

};

