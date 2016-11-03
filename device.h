/* for checkable device */
struct checkable_device 
{
	int trigger,type;
	double val,se,ee;
};

checkable_device *create_checkable(int type,double se,double ee);

void start_checking(checkable_device &dev);
void stop_checking(checkable_device &dev);

double get_checked_val(checkable_device &dev);
double get_checked_trigger(checkable_device &dev);
void clear_checked_trigger(checkable_device &dev);


/* for controllable_device */
struct controllable_device
{
	int status;
	int type;
};

controllable_device *create_controllable(int type);
