#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int data = 10;

int child_process()
{
	printf("Child process %d, data %d\n",getpid(),data);
	data = 20;
	printf("Child process %d, data %d\n",getpid(),data);
	_exit(0);
}

int main(int argc, char* argv[])
{
	int pid;
	//写时复制技术，当父子进程试图修改相应段的行为时，为子进程分配独立的物理空间
    //fork之后，子进程先执行还是父进程先执行，取决于操作系统的调度策略
	//本机是 父进程先执行
    pid = fork();
	if(pid==0) {
		child_process();
	}
	else{
		sleep(1);
		printf("Parent process %d, data %d\n",getpid(), data);
		exit(0);
	}
}
