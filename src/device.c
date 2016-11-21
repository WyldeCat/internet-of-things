#include"device.h"

struct check_device *create_check(int _type,double _se,double _ee,char *_label)
{
	// Not implemented.
	return NULL;
}

void *listen_dev(void *data)
{
	// NOT implemented.
}
double get_checked_val(struct check_device *dev)
{
	// Not implemented.
}

double get_checked_trigger(struct check_device *dev)
{
	// Not implemented.
}

void clear_checked_trigger(struct check_device *dev)
{
	// Not implemented.
}


struct control_device *create_control(int type,char *_label)
{
	// Not implemented.
	return NULL;
}
void control(struct control_device *dev,int command)
{
	// Not implemented.
}
