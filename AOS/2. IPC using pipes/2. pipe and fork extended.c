#include <stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main() {
 
    int fd[3][2];
    
    for(int i = 0;i<3;i++)
    {
        pipe(fd[i]);
    }
    
    int pid1 = fork();
    if(pid1==0){
        //child process 1
        dup2(fd[0][1],1);
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        execlp("ls","ls",NULL);
        close(fd[0][1]);
        return 0;
    }
    
    int pid2 = fork();
    if(pid2 == 0){
        dup2(fd[0][0],0);
        dup2(fd[1][1],1);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        execlp("more","more",NULL);
        close(fd[0][0]);
        close(fd[1][1]);
      
        return 0;
    }
    int pid3 = fork();
    if(pid3 == 0){
    dup2(fd[1][0],0);
    dup2(fd[2][1],1);
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][1]);
    close(fd[2][0]);
    
    execlp("grep","grep","pipe",NULL);
    close(fd[1][0]);
    close(fd[2][1]);
    
    
    
    
    return 0;
    }
    int pid4 = fork();
    if(pid4 == 0){
    dup2(fd[2][0],0);
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    
    
    execlp("wc","wc",NULL);
    close(fd[2][0]);
    }
    

    return 0;
}

