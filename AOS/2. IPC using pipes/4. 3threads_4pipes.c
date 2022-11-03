#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int fd[2];
int fd1[2];
int fd2[2];
int fd3[2];
void *thread1()
{
    
    char ch = 'a' ;
    while (1)
    {
        printf("thread1:\n");
        
        write(fd[1], &ch, sizeof(char));
        printf("Data written by thread 1 for thread 2: %c\n" , ch);
        if(ch=='c')
        break;
        sleep(3);
        printf("thread1::\n");
        read(fd1[0],&ch,1);
        printf("Data read by therad 1 by thread 2: %c\n",ch);
        printf("thread1::\n");
        read(fd3[0],&ch,sizeof(char));
        printf("data recieved from thread3 to thread1 : %c\n",ch);
        
    }
    // pthread_exit(NULL);
}

void *thread2()
{
   while (1)
    {
        sleep(1);
        printf("Thread2::\n");
        char ch;
        read(fd[0], &ch, 1);
        printf("Data read from Thread 1 by Thread 2: %c\n", ch);
        ch = ch +1;
        write(fd1[1],&ch,1);
        printf("Data written by Thread 2 for Thread 1 %c\n",ch);
        write(fd2[1],&ch,sizeof(char));
        printf("data sent from thread2 to thread3:%c\n",ch);

        sleep(3);
        if (ch == 'c')
        {
            break;
        }
        }
    // pthread_exit(NULL);
    
}

void *thread3()
{
    while(1)
    {
        sleep(1);
        printf("Thread3:\n");
        char ch;
        read(fd2[0],&ch,sizeof(char));

        printf("Data read from thread2 to thread3 %c\n",ch);

        printf("Data sent from thread3 to thread1 %c\n",ch);

        write(fd3[1],&ch,sizeof(char));

        if(ch=='c')
        {
            break;
        }

        sleep(1);
    }
}

int main()
{
    pipe(fd);
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pthread_t th[2];
    
    pthread_create(&th[0],NULL,&thread1,NULL);
    sleep(1);
    pthread_create(&th[1],NULL,&thread2,NULL);
    sleep(1);
    pthread_create(&th[2],NULL,&thread3,NULL);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);

    return 0;
}