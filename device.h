#include "constant.h"

/* for checkable device */
struct checkable_device 
{
	char label[10];
	int trigger,type;
	double val,se,ee;
};

checkable_device *create_checkable(int _type,double _se,double _ee,char *_label);

void start_checking(checkable_device *dev);
void stop_checking(checkable_device *dev);

double get_checked_val(checkable_device *dev);
double get_checked_trigger(checkable_device *dev);
void clear_checked_trigger(checkable_device *dev);


/* for controllable_device */
struct controllable_device
{
	char label[10];
	int status;
	int type;
};

controllable_device *create_controllable(int type,char *_label);
void control(controllable_device *dev,int command);
