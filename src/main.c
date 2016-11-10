#include<stdio.h>

#include"constant.h"
#include"rule.h"
#include"device.h"

checkable_device (*chk_devs)[CHK_DEV_NUM];
controllable_device (*con_devs)[CON_DEV_NUM];
rule (*rules)[RULE_NUM];

void init();

int main( )
{
	int i,j;

	init();

	while(1)
	{
		/* Critical section */
		for(i=0;i<RULE_NUM;i++)
		{
			if(rules[i].check()==true)
			{
				control(rules[i].con_dev,rules[i].command);
			}
		}
		for(i=0;i<CHK_DEV_NUM;i++)
		{
			clear_checked_trigger(chk_devs[i]);
		}
		// Not implemented.	
	}
	return 0;
}

void init()
{
	int i;
	for(i=0;i<CHK_DEV_NUM;i++)
	{
		if(chk_devs[i]!=NULL)
		{
			chk_devs[i]->start_checking();
		}
	}
	return;
}
