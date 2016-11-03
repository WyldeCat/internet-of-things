#define "device.h"
#define "constant.h"

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
