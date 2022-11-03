#include<signal.h>
#include<stdio.h>

int pid;

void sig_handler(int s)
{
    printf("inside handler the process id of the parent is:%d\n",pid);
    kill(pid,SIGKILL);
}

int main(){

    int t;
    pid = getpid();
    printf("parent process id:%d\n",pid);
    t = fork();

    if(t==0)
    {
        printf("The process id of the child whose gonna kill the parent:%d\n",getpid());
        signal(SIGUSR1,sig_handler);
        raise(SIGUSR1);
    }
    else{
        sleep(2);
        printf("else part\n");
        printf("\nremaining parent process waiting to be executed\n");

    }
}
