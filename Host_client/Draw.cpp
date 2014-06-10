#include "Draw.h"


Draw::Draw(std::vector<Kortti> *k, sf::RenderWindow *w)
{
	Hand = k;
	clientWindow = w;
	if (!spades.loadFromFile("Resources/spade.png"))
	{
		std::cout << "SPADET FAILAS" << std::endl;
	}
	if (!clubs.loadFromFile("Resources/club.png"))
	{
		std::cout << "NUIJASTA TURPAA" << std::endl;
	}
	if (!diamonds.loadFromFile("Resources/diamond.png"))
	{
		std::cout << "TIMANTIT EI OO IKUISIAAA" << std::endl;
	}
	if (!hearts.loadFromFile("Resources/heart.png"))
	{
		std::cout << "SYDÄN PETTI" << std::endl;
	}
}
Draw::~Draw(void)
{
}

void Draw::drawLoop()
{
	

		sf::RectangleShape handCard(sf::Vector2f(150,240));
		handCard.setFillColor(sf::Color::Yellow);
		sf::RectangleShape topCard(sf::Vector2f(50,80));
		topCard.setFillColor(sf::Color::Yellow);
		sf::RectangleShape currentCard(sf::Vector2f(50,80));
		currentCard.setFillColor(sf::Color::Yellow);
		sf::Sprite icon;

		int counter = 1;
		for (int i = 0; i < Hand->size(); i++)
		{
			if(Hand->at(i).suit == Hearts)
				icon.setTexture(hearts);
			if(Hand->at(i).suit == Diamonds)
				icon.setTexture(diamonds);
			if(Hand->at(i).suit == Clubs)
				icon.setTexture(clubs);
			if(Hand->at(i).suit == Spades)
				icon.setTexture(spades);
			icon.setPosition(160*counter,750);
			handCard.setPosition(160*counter,750);
			counter++;
			clientWindow->draw(handCard);
			clientWindow->draw(icon);
			
		}




}
