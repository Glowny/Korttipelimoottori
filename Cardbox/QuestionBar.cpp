#include "QuestionBar.h"


QuestionBar::QuestionBar(std::string who, std::string what,sf::Vector2f pos)
{
	sf::Font *font = new sf::Font;
	font->loadFromFile("comic.ttf");
	question.setFont(*font);
	yes.setFont(*font);
	no.setFont(*font);
	question.setColor(sf::Color::Black);
	yes.setColor(sf::Color::Black);
	no.setColor(sf::Color::Black);
	bar.setSize(sf::Vector2f(500,100));
	yesbar.setSize(sf::Vector2f(50,50));
	nobar.setSize(sf::Vector2f(50,50));
	question.setString(who+" wants to "+what);
	yes.setString("yes");
	no.setString("nope");
	setPos(pos);
	arrange();
}

void QuestionBar::arrange()
{
	float ratioy;
	float ratiox;
	ratiox = bar.getGlobalBounds().width/question.getGlobalBounds().width;
	ratioy = (bar.getGlobalBounds().height/question.getGlobalBounds().height);
	ratioy*=0.5f;
	question.scale(ratiox,ratioy);

	ratiox = yesbar.getGlobalBounds().width/yes.getGlobalBounds().width;
	ratioy = (yesbar.getGlobalBounds().height/yes.getGlobalBounds().height);
	ratioy*=0.5f;
	yes.scale(ratiox,ratioy);

	ratiox = nobar.getGlobalBounds().width/no.getGlobalBounds().width;
	ratioy = (nobar.getGlobalBounds().height/no.getGlobalBounds().height);
	ratioy*=0.5f;
	no.scale(ratiox,ratioy);
}

int QuestionBar::checkClick(sf::Vector2i pos)
{
	if(yesbar.getGlobalBounds().contains(sf::Vector2f(pos)))
		return true;
	if(nobar.getGlobalBounds().contains(sf::Vector2f(pos)))
		return false;
	return -1;

}

void QuestionBar::setPos(sf::Vector2f pos)
{
	bar.setPosition(pos);
	yesbar.setPosition(bar.getGlobalBounds().left+bar.getGlobalBounds().width,bar.getGlobalBounds().top);
	nobar.setPosition(bar.getGlobalBounds().left+bar.getGlobalBounds().width,bar.getGlobalBounds().top+yes.getGlobalBounds().height);
	yes.setPosition(bar.getGlobalBounds().left+bar.getGlobalBounds().width,bar.getGlobalBounds().top+yesbar.getGlobalBounds().height*0.5f);
	no.setPosition(bar.getGlobalBounds().left+bar.getGlobalBounds().width,bar.getGlobalBounds().top+yes.getGlobalBounds().height+nobar.getGlobalBounds().height*0.5f);
}

void QuestionBar::draw(sf::RenderWindow &window)
{
	window.draw(bar);
	window.draw(yesbar);
	window.draw(nobar);
	window.draw(question);
	window.draw(yes);
	window.draw(no);
}

QuestionBar::~QuestionBar(void)
{
}