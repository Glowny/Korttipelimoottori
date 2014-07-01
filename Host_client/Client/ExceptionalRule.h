#pragma once
#include "rule.h"
class ExceptionalRule :
	public Rule
{
public:
	ExceptionalRule(EXCEPTION_TYPE type, EXCEPTION_OUTCOME outcome){_type = type; _outcome = outcome;}
	ExceptionalRule(EXCEPTION_TYPE type, Card specifiedCard, EXCEPTION_OUTCOME outcome)
	{_type = type; _specifiedCard = specifiedCard; _outcome = outcome;}

	~ExceptionalRule(void);

	EXCEPTION_OUTCOME check(Hand selectedCards);

	EXCEPTION_TYPE _type;
	EXCEPTION_OUTCOME _outcome;
	Card _specifiedCard;
};