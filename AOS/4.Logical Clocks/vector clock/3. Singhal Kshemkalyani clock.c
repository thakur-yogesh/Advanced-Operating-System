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

void print(int clock[]){
    for(int i = 0;i<MAX_PROCESS;i++)
    {
        printf("%d ",clock[i]);
    }
    printf("\n");
}

void update_last_sent(int last_sent[],int clock[])
{
    for(int i = 0;i<MAX_PROCESS;i++)
    {
        last_sent[i] = clock[i];
    }
}

void *thread1()
{
    struct tuple diff[MAX_PROCESS];

    printf("processs p1:: \n");
     
    int last_sent[MAX_PROCESS] = {0,0,0,0};
    int v_c1[MAX_PROCESS] = {0,0,0,0};

    //event 1 at process 1 happend

    v_c1[0]++;

    //sending the clock values to process2, but before sending checking the changed values from last_sent vector;

    printf("event 1 at processs p1\n");

    print(v_c1);

    int rows;
    int tuple_row = 0;

    for(int i = 0;i<MAX_PROCESS;i++)
    {
        if(v_c1[i]!=last_sent[i])
        {
            diff[tuple_row].data = v_c1[i];
            diff[tuple_row].index = i;
            tuple_row++;
        }
    }

    rows = tuple_row;
    tuple_row = 0;

    //now sending the changes from p1 to p2

    //printf("changes in the clock values  sent from process1 to process2\n");

    write(fd1[1],&rows,sizeof(int));
    write(fd1[1],diff,sizeof(struct tuple)*rows);
    //recoding the sent clock value in last_sent vector
    update_last_sent(last_sent,v_c1);

}

void *thread2()
{
    sleep(1);

    printf("process2::\n");

    struct tuple diff[MAX_PROCESS];

    int v_c2[MAX_PROCESS] = {0,0,0,0};
    int last_sent[MAX_PROCESS] = {0,0,0,0};

    //event 1 in process2 that starts 
    v_c2[1]++;

    int rows;
    read(fd1[0],&rows,sizeof(int));
    read(fd1[0],diff,sizeof(struct tuple)*rows);

    //diffrences recieved from process 1

    for(int i = 0;i<rows;i++)
    {
        printf("index: %d data: %d\n",diff[i].index,diff[i].data);
        v_c2[diff[i].index] = diff[i].data;
    }

   printf("Event 1 of process2\n");
   print(v_c2);
   sleep(2);

   printf("process2::\n");

   read(fd2[0],&rows,sizeof(int));
   read(fd2[0],diff,sizeof(struct tuple)*rows);
   
   //differences recieved from process 3 and event 2 of process 2 starts

   v_c2[1]++;

   for(int i = 0;i<rows;i++)
    {
        //printf("index: %d data: %d\n",diff[i].index,diff[i].data);
        v_c2[diff[i].index] = diff[i].data;
    }

   printf("event 2 of process2\n");
   print(v_c2);
   sleep(1);

   printf("process2::\n");
   read(fd2[0],&rows,sizeof(int));
   read(fd2[0],diff,sizeof(struct tuple)*rows);
   
   //differences recieved from process 3 and event 2 of process 2 starts

   v_c2[1]++;

   for(int i = 0;i<rows;i++)
    {
        //printf("index: %d data: %d\n",diff[i].index,diff[i].data);
        v_c2[diff[i].index] = diff[i].data;
    }

   printf("event 3 of process2\n");
   print(v_c2);
   sleep(3);

   //start of event of event 4 of process2;
   printf("process2::\n");

   read(fd2[0],&rows,sizeof(int));
   read(fd2[0],diff,sizeof(struct tuple)*rows);
   
   //differences recieved from process 3 and event 2 of process 2 starts

   v_c2[1]++;

   for(int i = 0;i<rows;i++)
    {
        //printf("index: %d data: %d\n",diff[i].index,diff[i].data);
        v_c2[diff[i].index] = diff[i].data;
    }

   printf("event 4 of process2\n");
   print(v_c2);




}

void *thread3()
{
    sleep(2);
    printf("Process3::\n");
    int v_c3[MAX_PROCESS] = {0,0,0,0};
    int last_sent[MAX_PROCESS] = {0,0,0,0};
    struct tuple diff[MAX_PROCESS];

    //event 1 of process 3 starts;
    v_c3[2]++;
    int rows;
    int tuple_row = 0;

    for(int i = 0;i<MAX_PROCESS;i++)
    {
        if(v_c3[i]!=last_sent[i])
        {
            diff[tuple_row].data = v_c3[i];
            diff[tuple_row].index = i;
            tuple_row++;
        }
    }

    rows = tuple_row;
    tuple_row = 0;
    printf("event 1 at process 3\n");
    print(v_c3);
    write(fd2[1],&rows,sizeof(int));

    write(fd2[1],diff,sizeof(struct tuple)*rows);

    update_last_sent(last_sent,v_c3);
    //printf("changes in the clock values sent from procsess3 to process2\n");

    sleep(1);
     printf("Process 3::\n");
    //event 3 at process3 starts
    v_c3[2]++;
    for(int i = 0;i<MAX_PROCESS;i++)
    {
        if(v_c3[i]!=last_sent[i])
        {
            diff[tuple_row].data = v_c3[i];
            diff[tuple_row].index = i;
            tuple_row++;
        }
    }
    rows = tuple_row;
    tuple_row = 0;

    printf("event 2 at process 3\n");
    print(v_c3);
    write(fd2[1],&rows,sizeof(int));

    write(fd2[1],diff,sizeof(struct tuple)*rows);

    update_last_sent(last_sent,v_c3);
    //printf("changes in the clock values sent from procsess3 to process2\n");
    sleep(2);
    
    printf("Process3::\n");

    //event 3 at process 3 starts

    v_c3[2]++;

    read(fd3[0],&rows,sizeof(int));
    read(fd3[0],diff,sizeof(struct tuple)*rows);

    for(int i = 0;i<rows;i++)
    {
        v_c3[diff[i].index] = diff[i].data;
    }

    printf("event 3 at process3 \n");
    print(v_c3);

    //start of event 4 at process 3;

    v_c3[2]++;
    for(int i = 0;i<MAX_PROCESS;i++)
    {
        if(v_c3[i]!=last_sent[i])
        {
            diff[tuple_row].data = v_c3[i];
            diff[tuple_row].index = i;
            tuple_row++;
        }
    }
    rows = tuple_row;
    tuple_row = 0;

    printf("event 4 at process 3\n");
    print(v_c3);
    write(fd2[1],&rows,sizeof(int));

    write(fd2[1],diff,sizeof(struct tuple)*rows);

    update_last_sent(last_sent,v_c3);
    //printf("changes in the clock values sent from procsess3 to process2\n");
    sleep(1);

    




}

void *thread4()
{
   sleep(4);

   printf("process4::\n");
   int v_c4[MAX_PROCESS] = {0,0,0,0};
   int last_sent[MAX_PROCESS] = {0,0,0,0};

   struct tuple diff[MAX_PROCESS];

    v_c4[3]++;

    //sending the clock values to process2, but before sending checking the changed values from last_sent vector;

    printf("event 1 at processs 4\n");

    print(v_c4);

    int rows;
    int tuple_row = 0;

    for(int i = 0;i<MAX_PROCESS;i++)
    {
        if(v_c4[i]!=last_sent[i])
        {
            diff[tuple_row].data = v_c4[i];
            diff[tuple_row].index = i;
            tuple_row++;
        }
    }

    rows = tuple_row;
    tuple_row = 0;

    //now sending the changes from p1 to p2

    //printf("changes in the clock values  sent from process4 to process3\n");

    write(fd3[1],&rows,sizeof(int));
    write(fd3[1],diff,sizeof(struct tuple)*rows);
    //recoding the sent clock value in last_sent vector
    update_last_sent(last_sent,v_c4);

    sleep(1);

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

    pthread_create(&th[3],NULL,&thread4,NULL);

    // pthread_create(&th[3],NULL,&thread4,NULL);



    // pthread_create(&th[2],NULL,&thread3,NULL);


    pthread_join(th[0],NULL);
    pthread_join(th[1],NULL);
    pthread_join(th[2],NULL);
    pthread_join(th[3],NULL);
    // pthread_join(th[2],NULL);





}