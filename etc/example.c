#include<stdio.h>

#include<wiringPi.h>
#include<wiringSerial.h>

int main( )
{
	int fd = serialOpen("/dev/ttyACM0",9600);

	while(1)
	{
		if(serialDataAvail (fd))
		{
			char tmp = serialGetchar(fd);
			printf("%c",tmp);
			fflush(stdout);
		}
	}
}
