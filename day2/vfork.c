#include <stdio.h>
#include <sched.h>
#include <unistd.h>

int data = 10;

int child_process()
{
	printf("Child process %d, data %d\n",getpid(),data);
	data = 20;
	printf("Child process %d, data %d\n",getpid(),data);
	_exit(0);
}

int main(int argc, char* argv[])
{// vfork 子进程共享父进程的虚拟空间和物理地址，和父进程完全一样, 所以子进程更改数据，父进程数据也会发生变化
	if(vfork()==0) {
		child_process();	
	}
	else{
		sleep(1);
		printf("Parent process %d, data %d\n",getpid(), data);
	}
}
