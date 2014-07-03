#pragma once
#include "rule.h"
class BasicRule
{
public:
	BasicRule(){}
	BasicRule(BASICRULE_TYPE type, BASICRULE_TRIGGER trigger):_type(type), _trigger(trigger){}
	~BasicRule(void){}

	BASICRULE_TYPE _type;
	BASICRULE_TRIGGER _trigger;
};