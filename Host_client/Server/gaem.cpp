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

	Hand currentPlayerHand;

	Card lastPlayed;

	Player lastPlayer;

	while(gameOn)
	{
		currentPlayerHand = server.getCurrentPlayer().getHand();

		Card topCard = server.getTopCard(TABLE_CENTER);

		if(topCard.suit != NULL && topCard.value != NULL)
		{
			if(lastPlayed != topCard)
				lastPlayer = server.getPreviousPlayer();
		}

		if(server.getCurrentPlayer() == lastPlayer)
				clear = true;

		lastPlayed = topCard;

		Hand playables;

			if(currentPlayerHand.hand.size() == 0)
			{
				server.winner();
				gameOn = false;
				break;
			}
	
			if(!clear)
			{
				for(int i = 0; i < currentPlayerHand.hand.size(); i++)
				{
					if(currentPlayerHand.hand[i].value > topCard.value)
						playables.add(currentPlayerHand.hand[i]);
				}
			}
			else
			{
				for(int i = 0; i < currentPlayerHand.hand.size(); i++)
				{
						playables.add(currentPlayerHand.hand[i]);
				}
				clear = false;
			}
		server.setPlayableCards(TABLE_CENTER, 1, playables);

		server.processTurn();
	}

	return 0;
}