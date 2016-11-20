#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <stdio.h>

#include "constant.h"
#include "rule.h"
#include "device.h"

checkable_device (*chk_devs)[CHK_DEV_NUM];
controllable_device (*con_devs)[CON_DEV_NUM];
rule (*rules)[RULE_NUM];

int init();
int readn(int fd, char* buf, int len);

int main( )
{
	int i,j;

	init();

	/*
	while(1)
	{
		// Critical section //
		for(i=0;i<RULE_NUM;i++)
		{
			if(rules[i].check()==true)
			{
				control(rules[i].con_dev,rules[i].command);
				// 2. When rule is satisfied, send UDP datagram.
			}
		}
		for(i=0;i<CHK_DEV_NUM;i++)
		{
			clear_checked_trigger(chk_devs[i]);
		}
		// Not implemented.	
	}
	*/
	return 0;
}

int init()
{
	// TCP server
	int ssock = socket(PF_INET,SOCK_STREAM,0);

	if(ssock == -1)
	{
		perror("socket()");
		return -1;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(4001);
	saddr.sin_addr.s_addr = INADDR_ANY;

	int option = true; // check
	socklen_t optlen = sizeof(option);
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);

	int ret = bind(ssock,(struct sockaddr*)&saddr,sizeof(saddr));
	if(ret == -1)
	{
		perror("bind()");
		return -1;
	}

	ret = listen(ssock,5); // Why 5?
	if(ret == -1)
	{
		perror("listen()");
		return -1;
	}
	
	while(true) 
	{
		struct sockaddr_in caddr;
		socklen_t size = sizeof(caddr);

		int csock = accept(ssock,(struct sockaddr*)&caddr,&size);
		if(csock == -1) 
		{
			perror("accept()");
			return -1;
		}

		char* client_ip = inet_ntoa(caddr.sin_addr);
		printf("Client %s connected..\n",client_ip);

		int n = 0;
		char buf[1024]={0,};
		char temp;
		int tmp=0;
		while (true)
		{
			tmp++;
			//scanf("%d",&tmp);
			temp='0'+(tmp%10);
			write(csock,&temp,1);
			printf("%d sended.\n",tmp);
			sleep(1);
			/*
			short len=0;
			n = readn(csock,(char*)&len,sizeof len);
			if (n == 0) 
			{
			    printf("end!\n");
				break;
			}
			else if (n == -1)
			{
				perror("read()");
				break;
			}
			printf("%d\n",len);
			n = readn(csock,buf,len);
			if (n == 0)
			{
				printf("end!\n");
				break;
			}
			else if (n == -1)
			{
				perror("read()");
				break;
			}
			printf("%s",buf);
			fflush(stdin);
			*/
		}
		close(csock);
	}
	close(ssock);
}

int readn(int fd,char* buf,int len)
{
	int n;
	int ret;

	n = len;
	while(n > 0)
	{
		ret = read(fd,buf,len);
		if (ret < 0)
		    return -1;
		if (ret == 0) // when fd's buffer is empty.
		    return len - n; //  

		buf += ret;
		n -= ret;
	}
	return len;
}
