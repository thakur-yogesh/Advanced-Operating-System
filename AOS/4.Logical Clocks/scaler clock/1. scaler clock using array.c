#include<stdio.h>
int main()
{
    int p1[10],p2[10];
    
    p1[0] = p2[0] = 0; // initial clock value;

    int e1 = 3; //number of events for p1;
    int e2 = 5; // number of events for p2;

    int p1__p2_send_event = 2, p1_recv_event_p2 = 3;
    int p2_p1_send_event = 4, p2_recv_event_p1 = 5;
    int 

    int p1_dependency_happend = 0;
    int p2_dependency_happend = 0;

    for(int i = 1;i<=e2;i++)
    {
        if(i==p1_recv_event_p2)
        {
           if(p1[i-1]<p2_p1_send_event)
           {
            p1[i] = p2_p1_send_event;
            p1[i]++;
           }
           else{
            p1[i] = p1[i-1] + 1;
           }
           p1_dependency_happend = 1;
        }

        if(i==p2_recv_event_p1)
        {
            if(p2[i-1]<p1__p2_send_event)
            {
               p2[i] = p1__p2_send_event;
               p2[i]++;
            }
            else{
                p2[i] = p2[i-1] + 1;
            }
            p2_dependency_happend = 1;
        }

        
        if(i<=e1&&(p1_dependency_happend==0))
        {
            p1[i] = p1[i-1] + 1;
        }

        if(i<=e2&&(p2_dependency_happend==0))
        {
            p2[i] = p2[i-1] + 1;
        }

        p1_dependency_happend = p2_dependency_happend = 0;
    }

    for(int i = 1;i<=e1;i++)
    {
        printf("%d ",p1[i]);
    }

    printf("\n");

    for(int i  = 1;i<=e2;i++)
    {
        printf("%d ",p2[i]);
    }



}