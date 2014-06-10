#pragma once
#include <iostream>
enum Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};

class Kortti
{
public:
	Kortti(int v, int s);
	~Kortti(void);
int value;
int suit;
};

