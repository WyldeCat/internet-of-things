#include<stdio.h>
#include<winsock.h>
#include<math.h>

int main()
{
	int sock;
	
	int data0, data1;

	struct sockaddr_in servAddr;
	unsigned int servPort=4001;

	char *servIP="127.0.0.1";
	
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed\n");
		exit(1);
	}

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		fprintf(stderr, "socket() failed\n");
		exit(1);
	}
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(servIP);
	servAddr.sin_port = htons(servPort);

	while (1)
	{
		int ret;
		char *test = "Hello world!";
		
		// need to think about protocol..

		ret = sendto(sock, test, strlen(test), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
		
		if (ret < 0)
		{
			fprintf(stderr, "sendto() failed : %d\n",ret);
			exit(1);
		}

		Sleep(1000);
	}
	return 0;
}