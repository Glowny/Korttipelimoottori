//#include "Server.h"
//
//int main()
//{
//	Server server;
//
//	int playerCount = 2;
//	server.initialize(playerCount);
//
//	server.setMultiplayType(SAME_VALUE);
//
//	server.setStartingHandSize(3);
//
//	server.setCardstoArea(SECONDARY_CARDS, 6);
//
//	server.setUp();
//
//	//kaikille jaetaan alussa kolme korttia k‰teen, kolme eteen v‰‰rinp‰in ja kolme n‰iden p‰‰lle oikeinp‰in
//	//oikeinp‰in olevia kortteja edest‰‰n voi ensimm‰isell‰ vuorollo vaihtaa k‰dess‰ oleviin
//	//voi pelata kortteja keskelle, pelattavan kortin valuen tulee olla suurempi tai sama kuin edellisen pelatun (kuvakortteja ei seiskaa pienemm‰lle)
//	//kymmpi kaataa sit‰ pienemm‰t kortit ja ‰ss‰ kuvat, 2 on suurin kortti eik‰ sit‰ voi kaataa
//	//jos tyhj‰‰n pˆyt‰‰n pelataan kaatokortti, on seuraavan pelaajan nostettava se suoraan
//	//samaa valuea olevia kortteja voi pelata useamman (nelj‰ saman arvoista korttia kaataa), k‰dess‰ pit‰‰ olla aina 3 korttia kunnes pakka loppuu, pelaaja jolta loppuu kortit ensin voittaa pelin
//	//k‰sikorttien loputtua pelataan ensin edest‰ oikeinp‰in olevat kortit ja t‰m‰n j‰lkeen yksikerrallaan v‰‰rinp‰in olleet
//	//jos pelaaja ei voi lyˆd‰ pelatun kortin p‰‰lle mit‰‰n, joutuu h‰n nostamaan pelatut kortit (saa kokeilla yhden pakan p‰‰lt‰ tai nostaa suoraan)
//
//	bool gameOn = true;
//
//	Hand currentPlayerHand;
//
//	Card lastPlayed;
//
//	Player lastPlayer;
//
//	while(gameOn)
//	{
//		currentPlayerHand = server.getCurrentPlayer().getHand();
//
//		Card topCard = server.getTopCard(TABLE_CENTER);
//
//		if(topCard.suit != NULL && topCard.value != NULL)
//		{
//			if(lastPlayed != topCard)
//				lastPlayer = server.getPreviousPlayer();
//		}
//
//		//if(server.getCurrentPlayer() == lastPlayer)
//				//clear = true;
//
//		lastPlayed = topCard;
//
//		Hand playables;
//
//			if(currentPlayerHand.hand.size() == 0)
//			{
//				server.winner();
//				gameOn = false;
//				break;
//			}
//	
//			
//				for(int i = 0; i < currentPlayerHand.hand.size(); i++)
//				{
//					if(currentPlayerHand.hand[i].value >= topCard.value)
//						playables.add(currentPlayerHand.hand[i]);
//				}
//			
//		server.setPlayableCards(TABLE_CENTER, 1, playables);
//
//		server.processTurn();
//	}
//
//	return 0;
//}