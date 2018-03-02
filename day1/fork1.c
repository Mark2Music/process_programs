#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
	fork();
	printf("hello\n");
	fork();	
	printf("hello\n");
	while(1);
}
