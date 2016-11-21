#ifndef _RULE_H_
#define _RULE_H_

#include <stddef.h>

#include "device.h"
#include "constant.h"

struct rule 
{
	struct control_device *con_dev;
	struct check_device *chk_dev;

	int type,command;
	int hour,minute;
	double threshold;
};

struct rule *create_rule(int type,int command,int hour,int minute,double threshold);
bool check_rule(struct rule *r);

#endif
