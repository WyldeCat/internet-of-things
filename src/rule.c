#include"rule.h"

#include<stdlib.h>

struct rule *create_rule(int _type,int _command,int _hour,int _minute,double _threshold,struct control_device *_con_dev,struct check_device *_chk_dev)
{
	struct rule *tmp = malloc(sizeof(struct rule));
	tmp->type = _type;
	tmp->command = _command;
	tmp->hour = _hour;
	tmp->minute = _minute;
	tmp->threshold = _threshold;
	tmp->con_dev = _con_dev;
	tmp->chk_dev = _chk_dev;
	return tmp;
}

bool check_rule(struct rule *r)
{
	// Not implemented.
	return false;
}
