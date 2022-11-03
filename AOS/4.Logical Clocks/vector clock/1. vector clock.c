#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int fd1[2];
int fd2[2];
int fd3[2];

void *thread1()
{
    printf("process 1::\n");
    int arr1[3] = {0,0,0};

    arr1[0]++;   //event e1;
    
    int n = 3;
    write(fd1[1],&n,sizeof(int)); // channel between procses 1 and 2
    
    write(fd1[1],&arr1,sizeof(int)*n);

    printf("vector clock sent from process1  to process 2\n");
    sleep(4);

    arr1[0]++;

    arr1[0]++;

    int arr3[3];

    int n3;

    read(fd3[0],&n3,sizeof(int));

    read(fd3[0],&arr3,sizeof(int)*n3);

    printf("vector clock at the end of p1\n");

    for(int i = 0;i<3;i++)
    {
        if(arr3[i]>arr1[i])
        {
            arr1[i] = arr3[i];
        }
        if(i==0)
        {
            arr1[0]++;
        }
    }

    for(int i = 0;i<3;i++)
    {
        printf("%d ",arr1[i]);
    }

}

void *thread2()
{
    sleep(1);
    printf("process 2::\n");
    int arr2[3] = {0,0,0};

    int arr1[3];
    int n;

    read(fd1[0],&n,sizeof(int));

    read(fd1[0],&arr1,sizeof(int) * n);

    printf("vector clock from process 1 in process 2 recieved\n");

    for(int i = 0;i<n;i++)
    {
        printf("%d ",arr1[i]);
    }
    printf("\n");
    for(int i = 0;i<n;i++)
    {
        if(arr1[i]>arr2[i]){
            arr2[i] = arr1[i];//recieve event of p2;
        }
        if(i==1)
        {
            arr2[i]++;
        }
        printf("%d ",arr2[i]);
    }

    arr2[1]++; // local event of p2;

    printf("\nvector clock at the second end of p2\n");

    printf("%d ",arr2[0]);
    printf("%d ",arr2[1]);
    printf("%d \n ",arr2[2]);
    
    write(fd2[1],&n,sizeof(int));

    write(fd2[1],&arr2,sizeof(int) * n);

    sleep(1);
}

void *thread3()
{
    sleep(2);
    printf("process 3::\n");
    int local_clock3[3] = {0,0,0};

    int n = 3;

    local_clock3[2]++;

    local_clock3[2]++;

    write(fd3[1],&n,sizeof(int));

    write(fd3[1],&local_clock3,sizeof(int) * n);

    sleep(3);

    local_clock3[2]++;

    int arr2[3];
    int n2;

    read(fd2[0],&n2,sizeof(int));

    read(fd2[0],&arr2,sizeof(int) * n2);
    // printf("\n vector recieved in p3 from o2\n");
    // for(int i = 0;i<n;i++)
    // {
    //     printf("%d ",arr2[i]);
    // }

    for(int i = 0;i<n;i++)
    {
        if(arr2[i]>local_clock3[i])
        {
            local_clock3[i] = arr2[i];
        }
        if(i == 2)
        {
            local_clock3[2]++;
        }
    }
    
    printf("\nlocal vector clock of p3 at the end of p3\n");

    for(int i = 0;i<n;i++)
    {
        printf("%d ",local_clock3[i]);
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

    pthread_create(&th[2],NULL,&thread3,NULL);


    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);





}