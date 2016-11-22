#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <stddef.h>

#include "constant.h"

/************************************************/
/************ for check device **************/
/************************************************/

struct check_device 
{
	char *label;
	int type,trigger,csock;
	float val,se;
};

struct check_device *create_check(int _type,float _se,int _csock,char *_label);
void *listen_dev(void *data); // index
double get_val(struct check_device *dev);
int get_trigger(struct check_device *dev);
void clear_trigger(struct check_device *dev);

/************************************************/
/*********** for control device ************/
/************************************************/

struct control_device
{
	char *label;
	int csock,status;
	// How about read control number and it's label?
};

struct control_device *create_control(int _csock,int _status,char *_label);
void control(struct control_device *dev,int command);

#endif
