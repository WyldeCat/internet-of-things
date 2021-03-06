#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>

#include "constant.h"
#include "rule.h"
#include "device.h"

struct check_device *chk_devs[CHK_DEV_NUM];
pthread_t chk_thread[CHK_DEV_NUM];
struct control_device *con_devs[CON_DEV_NUM];
struct rule *rules[RULE_NUM];

void *accept_dev(void *data);

void load_sample_rule(); // test
int readn(int fd,char *buf,int len);
int chk_cnt,con_cnt,rule_cnt;

int main( )
{
	int i,j,ret;

	pthread_t thread_listen;
	pthread_create(&thread_listen,NULL,accept_dev,NULL);
	
	while(chk_cnt==0 || con_cnt==0);
	
	load_sample_rule();
	
	while(1)
	{
		for(i=0;i<rule_cnt;i++)
		{
			if(check_rule(rules[i])==true)
			{
				short command;
				if(rules[i]->command == COMMAND_ON) command=1;
				else if(rules[i]->command == COMMAND_OFF) command=0;
				else command = (rules[i]->con_dev->status == 0) ? 1 : 0;

				write(rules[i]->con_dev->csock,&command,sizeof(command));
			}
		}
	}
	pthread_join(thread_listen,(void **)&ret);
	return 0;
}

void *accept_dev(void *data)
{
	// TCP server
	int ssock = socket(PF_INET,SOCK_STREAM,0);

	if(ssock == -1)
	{
		perror("socket()");
		exit(1);
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(4001);
	saddr.sin_addr.s_addr = INADDR_ANY;

	int option = true;
	socklen_t optlen = sizeof(option);
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);

	int ret = bind(ssock,(struct sockaddr*)&saddr,sizeof(saddr));
	if(ret == -1)
	{
		perror("bind()");
		exit(1);
	}

	ret = listen(ssock,5);
	if(ret == -1)
	{
		perror("listen()");
		exit(1);
	}

	while(true)
	{
		struct sockaddr_in caddr;
		socklen_t size = sizeof(caddr);
		printf("accepting thread: Waiting...\n");
		fflush(stdout);
		int csock = accept(ssock,(struct sockaddr*)&caddr, &size);
		if(csock == -1)
		{
			perror("accept()");
			exit(1);
		}

		char* client_ip = inet_ntoa(caddr.sin_addr);
		printf("\naccepting thread: Client connected...!\n");
		fflush(stdout);

		int n = 0;
		short len,info[3];
		char buf[32]={0,};
		n = readn(csock,(char*)&info[0],sizeof(short));// type
		printf("accepting thread: type: %d\n",info[0]);
		n = readn(csock,(char*)&info[1],sizeof(short));// type2
		printf("accepting thread: type2: %d\n",info[1]);
		n = readn(csock,(char*)&info[2],sizeof(short));// threshold
		printf("accepting thread: threshold: %d\n",info[2]);
		n = readn(csock,(char*)&len,sizeof(short));
		n = readn(csock,buf,len);
		printf("accepting thread: label: %s\n\n",buf);

		if(n == -1)
		{
			exit(1);
		}
		if(info[0]==CHECK && chk_cnt<CHK_DEV_NUM)
		{
			chk_devs[chk_cnt]=create_check(info[1],info[2],csock,buf);
			pthread_create(&chk_thread[chk_cnt],NULL,listen_dev,(void*)chk_devs[chk_cnt]);
			chk_cnt++;
		}
		else if(info[0]==CONTROL && con_cnt<CON_DEV_NUM)
		{
			con_devs[con_cnt]=create_control(csock,info[1],buf);
			con_cnt++;
		}
		else 
		{
			printf("type error!\n");
			exit(1);
		}
	}
}


int readn(int fd,char* buf,int len)
{
	int n;
	int ret;

	n = len;
	while(n>0)
	{
		ret = read(fd,buf,len);
		if(ret < 0)
		{
			return -1;
		}
		if(ret == 0)
		{
			return len-n;
		}
		buf += ret;
		n -= ret;
	}
}

void load_sample_rule()
{
	rules[0]=create_rule(SIMPLE_RULE,MORE_THAN,COMMAND_ON,0,0,5.0,con_devs[0],chk_devs[0]);
	rules[1]=create_rule(SIMPLE_RULE,LESS_THAN,COMMAND_OFF,0,0,5.0,con_devs[0],chk_devs[0]);
	rule_cnt=2;
}
