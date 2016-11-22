#include"device.h"

#include<stdlib.h>
 
struct check_device *create_check(int _type,double _se,double _ee,int _csock,char *_label)
{
	struct check_device *tmp = malloc(sizeof(struct check_device));
	tmp->type = _type;
	tmp->se = _se;
	tmp->ee = _ee;
	tmp->csock = _csock;
	tmp->label = _label;
	return tmp;
}

void *listen_dev(void *data)
{
	// NOT implemented.
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

struct control_device *create_control(int _csock,char *_label)
{
	struct control_device *tmp = malloc(sizeof(struct control_device));
	tmp->csock = _csock;
	tmp->label = _label;
	return tmp;
}
void control(struct control_device *dev,int command)
{
	// Not implemented.
}
