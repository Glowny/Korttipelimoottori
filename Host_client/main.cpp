#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Kortti.h"
#include "Player.h"
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

	for (int i = 0; i < pCount; i++)
	{
		Player p(i);
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