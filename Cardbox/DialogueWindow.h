#pragma once
#include <SFML\Graphics.hpp>
#include "QuestionBar.h"
class DialogueWindow
{
public:
	DialogueWindow(void);
	~DialogueWindow(void);
	void addQuestion(std::string who, std::string what);
	void checkQuestions();
	void draw();
	void hide();
	void show();
	int getQuestionState(int index){/*haetaan pelaajan questionin tila jostain multimäpistä tai jostain, tai jotain :DDDD*/};
private:
	void arrange();
	sf::RenderWindow window;
	std::string who,what;
	std::vector<QuestionBar> questions;
};