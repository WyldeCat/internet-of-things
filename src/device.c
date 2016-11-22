#include"device.h"

#include<stdio.h>
#include<stdlib.h>
 
struct check_device *create_check(int _type,float _se,int _csock,char *_label)
{
	struct check_device *tmp = malloc(sizeof(struct check_device));
	tmp->type = _type;
	tmp->se = _se;
	tmp->csock = _csock;
	tmp->label = _label;
	return tmp;
}

void *listen_dev(void *data)
{
	struct check_device* dev = (struct check_device *)data;
	int csock = dev->csock;
	printf("listening thread: Hi. I'm listening %s in %d\n",dev->label,csock);
	fflush(stdout);
	while(true)
	{
		int n;
		float tmp;
		n = read(csock,(char*)&tmp,4);
		if(n==0)
		{
			printf("listening thread: Connection end : %s\n",dev->label); 
			break;
		}
		else if(n==-1)
		{
			perror("read()");
			break;
		}
		dev->val = tmp;
		printf("listening thread: %f received by %s\n",dev->val,dev->label);
		fflush(stdout);
	}
	
	//close(csock);
}

double get_checked_val(struct check_device *dev)
{
	// Not implemented.
}

int get_checked_trigger(struct check_device *dev)
{
	// Not implemented.
}

void clear_checked_trigger(struct check_device *dev)
{
	// Not implemented.
}

struct control_device *create_control(int _csock,int _status,char *_label)
{
	struct control_device *tmp = malloc(sizeof(struct control_device));
	tmp->csock = _csock;
	tmp->label = _label;
	tmp->status = _status;
	return tmp;
}
void control(struct control_device *dev,int command)
{
	// Not implemented.
}
