#include "Player.h"


Player::Player(std::string i)
{
	id = i;
}

Player::~Player(void)
{
}

Hand Player::getHand()
{
	return hand;
}

void Player::setHand(std::vector<Card> h)
{
	hand.setHand(h);
}

void Player::addCard(Card c)
{
	hand.add(c);
}

std::string Player::getID()
{
	return id;
}