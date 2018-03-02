#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
//#include <sys/types.h>
//#include <asm/unistd.h>

static pid_t gettid( void )
{
	return syscall(__NR_gettid);
}

static void *thread_fun(void *param)
{
	printf("thread pid:%d, tid:%d pthread_self:%lu\n", getpid(), gettid(),pthread_self());
	while(1);
	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2;
	int ret;

	printf("thread pid:%d, tid:%d pthread_self:%lu\n", getpid(), gettid(),pthread_self());
    
    /*
     *通过系统调用getrlimit() 获取线程栈的大小(参数中的RLIMIT_STACK)，在我的环境里(CentOS6)，      *     缺省值是8M。
     *调用mmap2()分配内存，大小为10489856字节，合10244K，比栈空间大了4K。返回0xb6d1c000。
     *调用mprotect()，设置个内存页的保护区(大小为4K)，页面起始地址为0xb6d1c000。这个页面用于监     *    测栈溢出，如果对这片内存有读写操作，那么将会触发一个SIGSEGV信号。下面布局图中的红色      *    区域既是。
     *调用clone()创建线程。调用的第一个参数是一个地址：栈底的地址(这里具体为0xb771c494)。栈空      *    间的内存使用，是从高位内存开始的。
     */
	ret = pthread_create(&tid1, NULL, thread_fun, NULL);
	if (ret == -1) {
		perror("cannot create new thread");
		return -1;
	}

	ret = pthread_create(&tid2, NULL, thread_fun, NULL);
	if (ret == -1) {
		perror("cannot create new thread");
		return -1;
	}

	if (pthread_join(tid1, NULL) != 0) {
		perror("call pthread_join function fail");
		return -1;
	}

	if (pthread_join(tid2, NULL) != 0) {
		perror("call pthread_join function fail");
		return -1;
	}

	return 0;
}
