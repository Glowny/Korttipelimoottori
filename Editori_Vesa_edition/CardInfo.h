#pragma once
class CardInfo
{
public:
	CardInfo(float cW, float cH, int amount);
	~CardInfo(void);
	void setCardAmount(int c[]);
	float getCardWidth();
	float getCardHeight();
	int getCardAmount();
	int* getCards();
private:
	float cardWidth;
	float cardHeight;
	int cardAmount;	// kuinka monta erityyppist� korttia on
	int cards[];	// kuinka monta kutakin erityyppist� korttia on
};

// oma read ja write niin kirjottaa aina oikeessa j�rjestyksess�
// tallentaa olion ja gettereill� arvot


