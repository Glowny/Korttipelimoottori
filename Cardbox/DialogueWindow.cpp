#include "DialogueWindow.h"


DialogueWindow::DialogueWindow(void):window(sf::RenderWindow(sf::VideoMode(550, 600), "Q"))
{
}

void DialogueWindow::addQuestion(int playerIndex, std::string who, std::string what)
{
	float posY = questionsMap.size()*100.f;
	questionsMap[playerIndex] = QuestionBar(who,what,sf::Vector2f(0, posY));
}

int DialogueWindow::checkQuestion(int index)
{
	sf::Event Event;

	while(window.pollEvent(Event))
	{
		switch(Event.type)
		{
		case sf::Event::MouseButtonPressed:
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mapIT = questionsMap.find(index);
					if(mapIT != questionsMap.end())
						return (*mapIT).second.checkClick(sf::Mouse::getPosition());
					return -1;
				}
		}
	}
}

void DialogueWindow::arrange()
{
	for(int i = 0; i < questionsMap.size(); i++)
	{
		questionsMap[i].setPos(sf::Vector2f(0, i*100.f));
	}
}

void DialogueWindow::hide()
{
	window.setActive(false);
	window.setVisible(false);
}

void DialogueWindow::show()
{
	window.setActive(true);
	window.setVisible(true);
}

void DialogueWindow::close()
{
	window.close();
}

void DialogueWindow::draw()
{
	for(int i = 0; i < questionsMap.size(); i++)
	{
		questionsMap[i].draw(window);
	}
}

DialogueWindow::~DialogueWindow(void)
{
}