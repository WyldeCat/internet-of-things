#ifndef _RULE_H_
#define _RULE_H_

#include <stddef.h>

#include "device.h"
#include "constant.h"

struct rule 
{
	struct control_device *con_dev;
	struct check_device *chk_dev;

	int type,type2,command;
	int hour,minute;
	float threshold;
};
struct rule *create_rule(int _type,int _type2,int _command,int _hour,int _minute,float _threshold,struct control_device *_con_dev,struct check_device *_chk_dev);
bool check_rule(struct rule *r);

#endif
