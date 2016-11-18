#ifndef _RULE_H_
#define _RULE_H_

#include "device.h"
#include "constant.h"

struct rule 
{
	controllable_device *con_dev;
	checkable_device *chk_dev;

	int type,command;
	int hour,minute;
	double threshold;
};

rule *create_rule(int type,int command,int hour,int minute,double threshold);
bool check_rule(rule *r);

#endif
