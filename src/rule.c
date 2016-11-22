#include"rule.h"

#include<stdlib.h>

struct rule *create_rule(int _type,int _type2,int _command,int _hour,int _minute,float _threshold,struct control_device *_con_dev,struct check_device *_chk_dev)
{
	struct rule *tmp = malloc(sizeof(struct rule));
	tmp->type = _type;
	tmp->type2 = _type2;
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
	if(r->type == INTERACTIVE_RULE)
	{
		bool ismore=(r->type2 == MORE_THAN);
		if(r->chk_dev->val >= r->threshold) return ismore;
		else return !ismore;
	}
	else if(r->type == TRIGGER_RULE)
	{
		if(r->chk_dev->trigger==1)
		{
			return true;
			r->chk_dev->trigger=0;
		}
		return false;
	}
	else 
	{
		//NOT Implemented.
	}
}
