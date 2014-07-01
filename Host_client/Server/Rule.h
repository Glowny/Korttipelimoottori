#pragma once
#include "Hand.h"

enum COMPARISON_TYPE{
	EMPTY_COMPARISON = -1,
	SMALLER,
	BIGGER,
	SAME,
	SMALLER_SAME,
	BIGGER_SAME,
};

enum COMPARISON_TARGET{
	OWN,
	OWN_TO_TABLE
};

enum EXCEPTION_TYPE{
	EMPTY_EXCEPTION = -1,
	EMPTY_PLAY,
	SPECIFIED_CARD,
};

enum EXCEPTION_OUTCOME{
	NOTHING,
	CLEAR_TABLE,
	PASKAA,
};


class Rule
{


public:
	Rule(void);
	virtual ~Rule(void);
	virtual bool check(Hand selectedCards, Hand tableCards) = 0;
};