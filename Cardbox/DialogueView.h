#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include "QuestionBar.h"
class DialogueView
{
public:
	DialogueView(void);
	~DialogueView(void);
	void addQuestion(int index, std::string who, std::string what);
	int checkQuestion(int index, sf::Vector2i mousePos);
	void draw(sf::RenderWindow &window);
private:
	void arrange();
	std::string who,what;
	std::map<int, QuestionBar> questionsMap;
	std::map<int, QuestionBar>::iterator mapIT;
};