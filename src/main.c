#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdio.h>

#include "constant.h"
#include "rule.h"
#include "device.h"

struct check_device *chk_devs[CHK_DEV_NUM];
pthread_t chk_thread[CHK_DEV_NUM];
struct control_device *con_devs[CON_DEV_NUM];
struct rule *rules[RULE_NUM];

void *accept_dev(void *data);
int chk_cnt;
int readn(int fd,char *buf,int len);

int main( )
{
	int i,j,ret;

	pthread_t thread_listen;
	pthread_create(&thread_listen,NULL,accept_dev,NULL);

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

		int csock = accept(ssock,(struct sockaddr*)&caddr, &size);
		if(csock == -1)
		{
			perror("accept()");
			exit(1);
		}

		char* client_ip = inet_ntoa(caddr.sin_addr);
		printf("Client %s connected..\n",client_ip);

		int n = 0;
		short len,info[4];
		char buf[32]={0,};
		
		n = readn(csock,(char*)info[0],sizeof(short));// type
		n = readn(csock,(char*)info[1],sizeof(short));// type2
		n = readn(csock,(char*)info[2],sizeof(short));// start
		n = readn(csock,(char*)info[3],sizeof(short));// end
		n = readn(csock,(char*)len,sizeof(short));
		n = readn(csock,buf,len);
		if(n <= 0)
		{
			exit(1);
		}
		if(info[0]==CHECKING)
		{
			chk_devs[chk_cnt]=create_check(info[1],info[2],info[3],buf);
			pthread_create(&chk_thread[chk_cnt],NULL,listen_dev,NULL);
			chk_cnt++;
		}
		else 
		{
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
