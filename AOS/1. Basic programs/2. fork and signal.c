#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void handler(int s)
{
pid_t pid;
pid = wait(NULL);
printf("the process id is: %d\n",pid );
signal(SIGCHLD,handler);
}

int main()
{

int i;
signal(SIGCHLD, handler);
for(i=0;i<2;i++)
switch(fork())
{
   case 0:
   printf("child has been created %d\n",getpid());
   exit(0);
}
  sleep(2);
}
