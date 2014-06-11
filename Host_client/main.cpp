#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Kortti.h"
#include "Player.h"
#include "Draw.h"
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int myrandom (int i) {return std::rand()%i;}
void host()
{
	std::vector<Player> Players;
	std::vector<Kortti> mainDeck;
	int playerTurn = 0;
	std::cout << "Give player count" << std::endl;
	int pCount;
	std::cin >> pCount;

	// socketit yhdistell‰‰n, ja kysell‰‰n nimet;
	std::vector<std::string> names;
	names.push_back("Jyrki");
	names.push_back("Jyrki2");
	for (int i = 0; i < pCount; i++)
	{
		Player p(i,names[0]);
		Players.push_back(p);
	}

	// socketti ykkˆselle annetaan Players[0].getPNumber(), kakkoselle Players[1].getPNumber() jne..

	for (int i = 1; i < 13; i++)
	{
		Kortti h(i, Hearts);
		Kortti d(i, Diamonds);
		Kortti c(i, Clubs);
		Kortti s(i, Spades);

		mainDeck.push_back(h);
		mainDeck.push_back(d);
		mainDeck.push_back(c);
		mainDeck.push_back(s);
	}

	std::srand (unsigned ( std::time(0) ) );

	std::random_shuffle ( mainDeck.begin(), mainDeck.end(), myrandom);
	int cardCounter = 0;
	for (int i = 0; i < pCount; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Players[i].addCard(mainDeck[cardCounter]);			// kaatuu jos paljo peeelaaajia
			cardCounter++;
		}
	}

	// L‰hetet‰‰n nimettyjen sockettien mukaan jokaiselle pelaajalle omat korttinsa

	int biggestValue=0;
	int winner;
	while (playerTurn < pCount+1) 		// toistetaan kunnes pelaajat ovat pelanneet yhden kortin, eli pelaajam‰‰r‰n verran.
	{
		// Kerrotaan Players[playerTurn] ett‰ on sen vuoro alkaa tekee kepposia, 
		// Odotetaan korttia joka tulee, ja laitetaan kaikille muille pelaajille socketin kautta tieto kortista.
		Kortti temp(2, Hearts);
		if (temp.value > biggestValue)
		{
			biggestValue = temp.value;
			winner = playerTurn;
		}
		playerTurn++;

	}
	// l‰hetet‰‰n winner kaikille
}
void client()
{

	

	sf::Vector2f cardSize(150,240);
	Kortti topCard(0,0);
	Kortti currentCard(0,0);
	// liityt‰‰n hostiin. Odotetaan ett‰ hosti antaa tiedon numerosta

	int pNumber = 2; // hostin tieto numerosta t‰h‰n
	// odotellaan kortteja

	std::vector<Kortti> Hand;
	// Hand = socketin kautta tullut korttivektori
	
	// pist‰n v‰liaikasesti muutaman kortin
	Kortti a (3,Diamonds);
	Kortti b (4,Clubs);
	Kortti c (9,Hearts);
	Kortti d (6,Diamonds);
	Kortti e (7,Spades);
	Kortti f (2,Clubs);
	Kortti g (1,Spades);
	Hand.push_back(a);
	Hand.push_back(b);
	Hand.push_back(c);
	Hand.push_back(d);
	Hand.push_back(e);
	Hand.push_back(f);
	Hand.push_back(g);

	std::vector<sf::FloatRect> areaVector;

	bool gameOver = false;
	sf::RenderWindow clientWindow(sf::VideoMode(1500,1000), "Master of card games");

	int cardsOnHand = 0;
	bool mousePressed = 0;
	while(clientWindow.isOpen() && gameOver == false)
	{
		sf::Event event;
		while (clientWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				clientWindow.close();
		}
		clientWindow.clear(sf::Color::Magenta);

	Draw drawSys(&Hand, &clientWindow, &topCard,&currentCard, cardSize);

	if(cardsOnHand != Hand.size())
	{
		areaVector.clear();
		float positionX = clientWindow.getSize().x/Hand.size();
		for (int i = 0; i < Hand.size(); i++)
		{
			sf::FloatRect area(i*positionX,750,cardSize.x,cardSize.y);
				areaVector.push_back(area);
		}
		cardsOnHand = Hand.size();
	
	}

			// odotetaan viesti‰ onko MAAILMANLOPPU TULLUT gameOver = true;
			// odotetaan viesti‰ onko minu vuoro
	int selection;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)==0)
	{
		mousePressed = 0;
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed == 0)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(clientWindow);
		mousePressed = 1;
		for(int i = 0; i < areaVector.size(); i++)
		{
			if (areaVector[i].left < mousePosition.x && areaVector[i].top < mousePosition.y && areaVector[i].left+areaVector[i].width > mousePosition.x && areaVector[i].top+areaVector[i].height > mousePosition.y)
			{
				currentCard = Hand[i];
				Hand.erase(Hand.begin()+i);
				areaVector.erase(areaVector.begin()+i);
			}
		}
	}

		if ( topCard.value < currentCard.value)
			topCard = currentCard;


		drawSys.drawLoop();
		clientWindow.display();
		}

}
int main()
{
	std::cout << "Ootko naa renki(0) vai isanta(1)" << std::endl;
	bool a;
	std::cin >> a;
	if (a)
	host();
	else
	client();
	system("PAUSE");
	return 0;
}