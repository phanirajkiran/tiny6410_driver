/*
*	平台设备对应的应用程序 
*	使用格式� argv[0] <0|1>
*	内部实现了ioctl来进行命令控制
*	在平台设备驱动中修改需要控制的引脚，而平台驱动中保持不变即可;只是为了
*	示例驱动中的分层和分离设计思想
*
*/



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void print_usage(char *name)
{
	printf("Usage:\n");
	printf("%s <0|1>\n",name);
}

int main(int argc,char **argv)
{
	
	int fd = 0;
	char buf[4]={0x1,0x2,0x3,0x4};
	unsigned long  rbuf = 0;

	if(argc != 2){
		print_usage(argv[0]);
		return -1;
	}
	fd = open("/dev/platleds",O_RDWR);

	if(fd < 0){
		printf("open /dev/leds error.\n");
		return -1;
	}
	
	rbuf = strtoul(argv[1],0,10);
	if(!rbuf){
		ioctl(fd,0,0);//关闭
	}else if(rbuf == 1){
		ioctl(fd,1,0);//打开
	}else{
		print_usage(argv[0]);
		return -1;
	}
	close(fd);
	return 0;
}

