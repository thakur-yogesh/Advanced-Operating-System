#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
int sum = 0;

void *routine(void *arg)
{
    int *n = (int*)arg;
    sum = sum + *n;
}

int main()
{
    int a[5];
    srand(time(NULL));
    for(int i = 0;i<5;i++)
    {
        a[i] = rand()%10 + 1;
        printf("generated : %d\n",a[i]);
    }

    pthread_t th[5];

    for(int i = 0;i<5;i++)
    {
        if(pthread_create(&th[i],NULL,&routine,&a[i]))
        {
            return 1;
        }
    }
    for(int i = 0;i<5;i++)
    {
        if(pthread_join(th[i],NULL)){
            return 1;
        }
    }
    printf("the sum is %d",sum);
}