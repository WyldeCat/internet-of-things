#ifndef _CONSTANT_H_
#define _CONSTANT_H_

typedef enum { false,true } bool;

/* controllable-device type */
#define CONTROL 0
#define CHECK	1

/* command menu */
#define POWER_ON 10
#define POWER_OFF 11

/* checkable-device type */
#define TRIGGER_ABLE 100
#define NORMAL 101

/* rule type */
#define TIME_RULE 1000
#define TRIGGER_RULE 1001
#define SIMPLE_RULE 1002

#define MORE_THAN 2000
#define LESS_THAN 2001
#define EQUAL 2002

#define COMMAND_ON 10000
#define COMMAND_OFF 10001
#define COMMAND_CONVERT 10002

/* NUM */
#define CON_DEV_NUM 10
#define CHK_DEV_NUM 10
#define RULE_NUM 10

#endif
