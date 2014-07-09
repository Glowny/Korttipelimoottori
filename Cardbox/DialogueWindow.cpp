#include "DialogueWindow.h"


DialogueWindow::DialogueWindow(void):window(sf::RenderWindow(sf::VideoMode(550, 600), "Q"))
{
}

void DialogueWindow::addQuestion(std::string who, std::string what)
{
	float posY = questions.size()*100.f;
	questions.push_back(QuestionBar(who,what,sf::Vector2f(0, posY)));
}

void DialogueWindow::checkQuestions()
{
	sf::Event Event;

	while(window.pollEvent(Event))
	{
		switch(Event.type)
		{
		case sf::Event::MouseButtonPressed:
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					for(int i = 0; i < questions.size(); i++)
					{
						//if(questions[i].checkClick(sf::Mouse::getPosition()) == 1)
					}
				}
		}
	}
}

void DialogueWindow::arrange()
{
	for(int i = 0; i < questions.size(); i++)
	{
		questions[i].setPos(sf::Vector2f(0, i*100.f));
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

void DialogueWindow::draw()
{
	for(int i = 0; i < questions.size(); i++)
	{
		questions[i].draw(window);
	}
}

DialogueWindow::~DialogueWindow(void)
{
}