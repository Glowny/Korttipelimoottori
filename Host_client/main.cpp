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
	std::string name;
	std::cout << "giv neim, pls"<<std::endl;
	std::cin >> name;

	int ip;
	std::cout << "giv ip, plz" << std::endl;
	std::cin >> ip;
	
	int topCard = 0;
	int currentCard;
	// liityt‰‰n hostiin. Odotetaan ett‰ hosti antaa tiedon numerosta

	int pNumber = 2; // hostin tieto numerosta t‰h‰n
	// odotellaan kortteja

	std::vector<Kortti> Hand;
	// Hand = socketin kautta tullut korttivektori
	
	// pist‰n v‰liaikasesti muutaman kortin
	Kortti a (3,Diamonds);
	Hand.push_back(a);
	Hand.push_back(a);
	Hand.push_back(a);
	Hand.push_back(a);
	Hand.push_back(a);

	gameOver = false;
while(gameOver = false)
{
	// odotetaan viesti‰ onko MAAILMANLOPPU TULLUT
	// odotetaan viesti‰ onko minu vuoro

	int message = 2; // eli kenen vuoro, v‰liaikasesti 2;
	if (message == pNumber)
	{
		std::cout << "===========================" << std::endl;
		std::cout << "Valitse poistettava kortti" << std::endl;
		for (int i = 0; i < Hand.size(); i++)
		{
			std::cout << i <<"="<< Hand[i].suit << std::endl;
		}
		std::cout << "===========================" << std::endl;
		int selection;
		std::cin >> selection;
		currentCard = Hand[selection].value;
		Hand.erase(Hand.begin()+selection);
		if ( topCard < currentCard)
			topCard = currentCard;
	}
	else
	{
		//odotellaan hostila korttia jonka toinen pelaaja on pelannut
		//currentCard = hostilta tullu kortti
		if (topCard < currentCard)
			topCard = currentCard;
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