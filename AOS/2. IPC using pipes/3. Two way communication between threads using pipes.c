#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int fd[2];
int fd1[2];
void *writer()
{
    
    char ch = 'a' ;
    while (1)
    {
        printf("THREAD1 in action : ");
        
        write(fd[1], &ch, sizeof(char));
        printf("Data written by thread 1 for thread 2: %c\n" , ch);
        if(ch=='q')
        break;
        sleep(3);
    
        read(fd1[0],&ch,1);
        printf("Data read by therad 1 by thread 2: %c\n",ch);
        
    }
    // pthread_exit(NULL);
}

void *reader()
{
   while (1)
    {
        sleep(1);
        printf("THREAD 2 in acition : ");
        char ch;
        read(fd[0], &ch, 1);
        printf("Data read from Thread 1 by Thread 2: %c\n", ch);
        ch = ch +1;
        write(fd1[1],&ch,1);
        printf("Data written by Thread 2 for Thread 1 %c\n",ch);
        sleep(2);
        if (ch == 'q')
        {
            break;
        }
        }
    // pthread_exit(NULL);
    
}

int main()
{
    pipe(fd);
    pipe(fd1);
    pthread_t th[2];

    pthread_create(&th[0],NULL,&writer,NULL);
    sleep(1);
    pthread_create(&th[1],NULL,&reader,NULL);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);

    return 0;
}