#include "Draw.h"


Draw::Draw(std::vector<Kortti> *k, sf::RenderWindow *w, Kortti *tc, Kortti *cc, sf::Vector2f cS)
{
	Hand = k;
	clientWindow = w;
	topCard = tc;
	currentCard = cc;
	cardSize = cS;
	if(!font.loadFromFile("Resources/Amble-Regular.ttf"))
	{
		std::cout << "Fonttia ei loytynyt" << std::endl;
	}
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
	if(!suits.loadFromFile("Resources/suits_tilemap.png"))
	{
	}
}
Draw::~Draw(void)
{
}

	void Draw::drawHand()
	{
		sf::Text text;
		text.setFont(font);

		sf::RectangleShape handCardR(cardSize);
		handCardR.setFillColor(sf::Color::White);

		sf::Sprite icon;
		sf::IntRect rectPos(0,0,32,32);
		icon.setTexture(suits);
		int counter = 0;
		if (Hand->size() != 0)
		{
			float positionX = clientWindow->getSize().x/Hand->size();
			for (int i = 0; i < Hand->size(); i++)
			{
				rectPos = getRectPos(Hand->at(i).suit);

				char cardNumber = '0' + Hand->at(i).value;
				text.setString(cardNumber);

				handCardR.setPosition(counter*positionX,750);
				icon.setTextureRect(rectPos);
				icon.setPosition(handCardR.getPosition());
			
				text.setCharacterSize(cardSize.x/3);
				text.setColor(sf::Color::Black);
				text.setOrigin(37.5,37.5);
				text.setPosition(handCardR.getPosition().x + handCardR.getSize().x*0.5, handCardR.getPosition().y + handCardR.getSize().y*0.5);
			
				counter++;


				clientWindow->draw(handCardR);
				clientWindow->draw(icon);
				clientWindow->draw(text);
			}
		}
	}
	void Draw::drawTopC()
	{
		sf::Text text;
		text.setFont(font);

		sf::RectangleShape topCardR(cardSize*0.75f);
		topCardR.setFillColor(sf::Color::White);

		sf::IntRect rectPos = getRectPos(topCard->suit);
		
		sf::Sprite smallIcon;
		smallIcon.setTexture(suits);
		smallIcon.setScale(0.75f,0.75f);

		smallIcon.setTextureRect(rectPos);
		topCardR.setPosition(350,500);
		smallIcon.setPosition(topCardR.getPosition());

		char cardNumber = '0' +topCard->value;
		text.setString(cardNumber);

		text.setCharacterSize(40);
		text.setColor(sf::Color::Black);
		text.setPosition(topCardR.getPosition().x + 65, topCardR.getPosition().y + 90);

		clientWindow->draw(topCardR);
		clientWindow->draw(smallIcon);
		clientWindow->draw(text);
	}
	void Draw::drawCurrentC()
	{
		sf::Text text;
		text.setFont(font);

		sf::RectangleShape currentCardR(cardSize*0.75f);
		currentCardR.setFillColor(sf::Color::White);

		sf::IntRect rectPos = getRectPos(currentCard->suit);
		
		sf::Sprite smallIcon;
		smallIcon.setTexture(suits);
		smallIcon.setScale(0.75f,0.75f);

		smallIcon.setTextureRect(rectPos);
		currentCardR.setPosition(550,500);
		smallIcon.setPosition(currentCardR.getPosition());

		char cardNumber = '0' +currentCard->value;
		text.setString(cardNumber);

		text.setCharacterSize(40);
		text.setColor(sf::Color::Black);
		text.setPosition(currentCardR.getPosition().x + 65, currentCardR.getPosition().y + 90);

		clientWindow->draw(currentCardR);
		clientWindow->draw(smallIcon);
		clientWindow->draw(text);

		
	}
	void Draw::drawOtherP()
	{
	
	}
	sf::IntRect Draw::getRectPos(int s)
	{
		sf::IntRect rectPos(0,0,32,32);
		if(s == Hearts)
		{rectPos.left =32; rectPos.top = 0;}
		if(s == Diamonds)
		{rectPos.left =32; rectPos.top = 32;}
		if(s == Clubs)
		{rectPos.left =0; rectPos.top = 32;}
		if(s == Spades)
		{rectPos.left =0; rectPos.top = 0;}

		return rectPos;
	}

void Draw::drawLoop()
{
	drawHand();
	drawCurrentC();
	drawTopC();
}
