#include<stdio.h>
#include<unistd.h>

int main(){
int fd[2];
pipe(fd);

int pid1 = fork();

if(pid1 == 0)
{
    dup2(fd[1],1);
    close(fd[0]);
  
   execlp("ls","ls",NULL);
   close(fd[1]);
   return 0;
   
}

int pid2 = fork();
if(pid2 == 0)
{
   dup2(fd[0],0);
   close(fd[1]);
   execlp("wc","wc",NULL);
   close(fd[0]);
   return 0;

}

close(fd[0]);
close(fd[1]);
waitpid(pid1,NULL,0);
waitpid(pid2,NULL,0);

return 0;

}
