#include "Server.h"

int main()
{
	Server server;

	int playerCount = 2;
	server.initialize(playerCount);

	server.setMultiplayType(SAME_VALUE);

	int startingHand = 5;
	server.setUp(startingHand);

	std::vector<Player> players = server.getPlayers();

	//voi pelata kortteja keskelle, pelattavan kortin valuen tulee olla suurempi kuin edellisen pelatun
	//samaa valuea olevia kortteja voi pelata useamman, pelaaja jolta loppuu kortit ensin voittaa pelin
	//jos kukaan ei voi lyödä pelatun kortin päälle mitään, kortin pelannut pelaaja saa aloittaa tyhjälle pöydälle

	bool gameOn = true, clear = true;

	Hand currentPlayerHand, nextPlayerHand;

	Card lastPlayed;

	Player lastPlayer;

	while(gameOn)
	{
		server.run();

		Card topCard = server.getTopCard(TABLE_CENTER);

		if(topCard.suit != NULL && topCard.value != NULL)
		{
			if(lastPlayed != topCard)
				lastPlayer = server.getCurrentPlayer();
		}

		if(server.getCurrentPlayer() == lastPlayer)
				clear = true;

		lastPlayed = topCard;

		for(int i = 0; i < players.size(); i++)
		{
			if(players[i] == server.getCurrentPlayer())
			{
				if(i+1 == players.size())
					nextPlayerHand = players[i+1].getHand();
				else
					nextPlayerHand = players[0].getHand();
			}
		}

		if(currentPlayerHand.hand.size() == 0)
		{
			server.winner();
			gameOn = false;
			break;
		}

		Hand playables;
		
		if(!clear)
		{
			for(int i = 0; i < nextPlayerHand.hand.size(); i++)
			{
				if(nextPlayerHand.hand[i].value > topCard.value)
					playables.add(nextPlayerHand.hand[i]);
			}
		}
		else
		{
			for(int i = 0; i < nextPlayerHand.hand.size(); i++)
			{
					playables.add(nextPlayerHand.hand[i]);
			}
			clear = false;
		}
		server.setPlayableCards(TABLE_CENTER, 1, playables);

	}

	return 0;
}