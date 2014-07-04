#pragma once
#include "rule.h"
class ExceptionalRule
{
public:
	ExceptionalRule(){}
	ExceptionalRule(EXCEPTION_TYPE type, EXCEPTION_OUTCOME outcome):_type(type), _outcome(outcome){}
	ExceptionalRule(EXCEPTION_TYPE type, Card specifiedCard, EXCEPTION_OUTCOME outcome):
	_type(type), _specifiedCard(specifiedCard), _outcome(outcome){}

	~ExceptionalRule(void);

	EXCEPTION_OUTCOME check(Hand playedCards, Hand targetCards);

	EXCEPTION_TYPE _type;
	EXCEPTION_OUTCOME _outcome;
	Card _specifiedCard;
};