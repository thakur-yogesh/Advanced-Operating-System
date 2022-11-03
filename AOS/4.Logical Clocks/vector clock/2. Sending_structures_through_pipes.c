#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define MAX_PROCESS 4

int fd1[2];
int fd2[2];
int fd3[2];

struct tuple{
    int index;
    int data;
};

void *thread1()
{
    struct tuple diff[MAX_PROCESS];

    diff[0].data = 5;
    diff[0].index = 0;


    diff[1].data = 4;
    diff[1].index = 1;

    int rows = 2;

    write(fd1[1],&rows,sizeof(int));

    write(fd1[1],diff,sizeof(struct tuple)*rows);



}

void *thread2()
{
    sleep(2);
    struct tuple diff[MAX_PROCESS] = {0};
    int rows;

    read(fd1[0],&rows,sizeof(int));

    read(fd1[0],diff,sizeof(struct tuple) * rows);

    for(int i = 0;i<rows;i++)
    {
        printf("%d ",diff[i].data);
        printf("%d ",diff[i].index);
        printf("\n");
    }
}

int main()
{
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    printf("main\n");
    pthread_t th[4];

    pthread_create(&th[0],NULL,&thread1,NULL);

    pthread_create(&th[1],NULL,&thread2,NULL);

    // pthread_create(&th[2],NULL,&thread3,NULL);


    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    // pthread_join(th[2],NULL);





}