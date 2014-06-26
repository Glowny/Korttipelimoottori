#include "Server.h"
#include "Platform.h"

int main()
{
	int players = 2;
	Server server;
	Platform platform(server);

	platform.setUp(players, 6);
	bool win=0;
	int cardCounter = 1;
	while (!win)
	{
		Player lastPlayer = platform.getCurrentPlayer();
		
		if(lastPlayer.getHand().hand.size() == 0)
			{
				server.send(lastPlayer.getID() +" voitti");
				win = true;
			}
		CardPacket receivedCards = platform.processTurn();
		server.send(receivedCards);
		if(receivedCards._cards.hand.size() == 0)
		{
			cardCounter++;
			if (players != 1)
			{
				if (cardCounter == players)
				{
					Hand tempH;
					server.sendReplacement(CardPacket(players,tempH));
					cardCounter = 1;

					// tai käske clienttiä tyhjentämään pöytä
				}
			}
			else
			{
				Hand tempH;
				server.sendReplacement(CardPacket(players,tempH));
				cardCounter = 1;
				// tai käske clienttiä tyhjentämään pöytä
			}
				
		}
		else
			cardCounter = 1;
	
	}
	return 0;
}