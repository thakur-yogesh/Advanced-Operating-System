#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mutex;

int sum = 0;
int inc = 0;

void *routine()
{
    pthread_mutex_lock(&mutex);
    sum = sum + inc;
    printf("the sum is %d\n",sum);
    inc+=5;
    pthread_mutex_unlock(&mutex);
}


int main()
{
    pthread_t th[5];
    pthread_mutex_init(&mutex,NULL);
    for(int i = 0;i<5;i++)
    {
        pthread_create(&th[i],NULL,&routine,NULL);
    }
    for(int i = 0;i<5;i++)
    {
        pthread_join(th[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
}