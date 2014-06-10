#include "Player.h"


Player::Player(int n, std::string na)
{
	playerNumber = n;
	name = na;
}

Player::~Player(void)
{
}

void Player::addCard(Kortti k)
{
	deck.push_back(k);
}

std::vector<Kortti> Player::getDeck()
{
	return deck;
}

int Player::getPNumber()
{
	return playerNumber;
}