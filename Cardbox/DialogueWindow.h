#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include "QuestionBar.h"
class DialogueWindow
{
public:
	DialogueWindow(void);
	~DialogueWindow(void);
	void addQuestion(int playerIndex, std::string who, std::string what);
	int checkQuestion(int index);
	void draw();
	void hide();
	void show();
	void close();
private:
	void arrange();
	sf::RenderWindow window;
	std::string who,what;
	std::map<int, QuestionBar> questionsMap;
	std::map<int, QuestionBar>::iterator mapIT;
};