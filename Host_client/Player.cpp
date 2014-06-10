#include "Player.h"


Player::Player(int n)
{
	playerNumber = n;
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