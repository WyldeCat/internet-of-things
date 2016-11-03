#include<stdio.h>

#include"constant.h"
#include"rule.h"
#include"device.h"

checkable_device (*chk_devs)[10];
controllable_device (*con_devs)[10];
rule (*rules)[10];

void init();

int main( )
{
	int i,j;

	init();

	while(1)
	{
		// Not implemented.	
	}
	return 0;
}

void init()
{
	int i;
	for(i=0;i<10;i++) {
		if(chk_devs[i]!=NULL) chk_devs[i]->start_checking();
	}
	return;
}
