#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int fd1[2];
int fd2[2];
int fd3[2];

void *thread1()
{
    
    int clock[5];
    clock[0] = 0;

    clock[1] = clock[1-1] + 1;

    printf("time stamp of event 1 of process 1: %d \n",clock[1]);

    printf("\n");

    write(fd1[1],&clock[1],sizeof(int));

    sleep(3);
    
    clock[2] = clock[2-1] + 1;
    printf("time stamp of event 2 of process 1 : %d \n",clock[2]);
    clock[3] = clock[3-1] + 1;
    printf("time stamp of event 3 of process 1 : %d \n",clock[3]);

    int reciever;

    

    read(fd3[0],&reciever,sizeof(int));

    if(clock[4-1]<reciever)
    {
        clock[4] = reciever;
        clock[4]++; 
    }
    else{
        clock[4] = clock[4-1] + 1;
    }

    printf("event 4 of process 1: %d \n",clock[4]);


}

void *thread2()
{
    sleep(1);
    
    int clock[3];
    clock[0] = 0;
    int reciever;

    read(fd1[0],&reciever,sizeof(int));

    if(clock[1-1]<reciever)
    {
        clock[1] = reciever;
        clock[1]++;
    }
    printf("event1 of process2 : %d \n",clock[1]);
    clock[2] = clock[2-1] + 1;
    printf("event 2 of process 2: %d \n",clock[2]);

    write(fd2[1],&clock[2],sizeof(int));

}

void *thread3()
{
    sleep(1);
    
    int clock[5];
    clock[0] = 0;

    clock[1] = clock[1-1] + 1;
    
    printf("event 1 of process 3: %d \n",clock[1]);

    clock[2] = clock[2-1] + 1;

    printf("event 2 of process 3: %d \n",clock[2]);

    write(fd3[1],&clock[2],sizeof(int));

    sleep(2);
    
    clock[3] = clock[3-1] + 1;

    printf("event 3 of process 3: %d \n",clock[3]);



    int reciever;

    read(fd2[0],&reciever,sizeof(int));

    if(clock[4-1]<reciever)
    {
        clock[4] = reciever;
        clock[4]++;
    }
    else{
        clock[4] = clock[4-1] + 1;
    }

    printf("event 4 of process 3: %d \n",clock[4]);

}

int main()
{
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pthread_t th[3];

    pthread_create(&th[0],NULL,&thread1,NULL);
    pthread_create(&th[1],NULL,&thread2,NULL);
    pthread_create(&th[2],NULL,&thread3,NULL);

    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);
}