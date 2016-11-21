#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <stddef.h>

#include "constant.h"

/************************************************/
/************ for check device **************/
/************************************************/

struct check_device 
{
	char label[10];
	int trigger,type;
	double val,se,ee;
};

struct check_device *create_check(int _type,double _se,double _ee,char *_label);
void *listen_dev(void *data); // index + csock
double get_val(struct check_device *dev);
double get_trigger(struct check_device *dev);
void clear_trigger(struct check_device *dev);

/************************************************/
/*********** for control device ************/
/************************************************/

struct control_device
{
	char label[10];
	int status;
	int type;
};

struct control_device *create_control(int type,char *_label);
void control(struct control_device *dev,int command);

#endif
