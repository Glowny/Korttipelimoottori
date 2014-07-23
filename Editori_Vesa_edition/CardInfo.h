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
	int cardAmount;
	int cards[];
};

