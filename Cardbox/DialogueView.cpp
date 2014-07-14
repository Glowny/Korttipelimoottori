#include "DialogueView.h"


DialogueView::DialogueView(void)
{
}

void DialogueView::addQuestion(int index, std::string who, std::string what)
{
	float posY = questionsMap.size()*100.f;
	questionsMap[index] = QuestionBar(who,what,sf::Vector2f(0, posY));
}

int DialogueView::checkQuestion(int index, sf::Vector2i mousePos)
{
	mapIT = questionsMap.find(index);
	if(mapIT != questionsMap.end())
		return (*mapIT).second.checkClick(sf::Mouse::getPosition());
	return -1;
}

void DialogueView::arrange()
{
	for(int i = 0; i < questionsMap.size(); i++)
	{
		questionsMap[i].setPos(sf::Vector2f(0, i*100.f));
	}
}

void DialogueView::draw(sf::RenderWindow &window)
{
	for(int i = 0; i < questionsMap.size(); i++)
	{
		questionsMap[i].draw(window);
	}
}

DialogueView::~DialogueView(void)
{
}
