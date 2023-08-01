#include<stdio.h>
#include<stdlib.h>
#define MAXLINE 200
int main()
{
int n,fd[2];
pid_t pid;
char line[MAXLINE];
if(pipe(fd)<0)
printf("PIPE ERROR\n");
if((pid=fork())<0)
printf("FORK EOORRR\n");

if(pid==0)
{
close(fd[1]);//for flusing the buffer
printf("child process from pipe\n");
n = read(fd[0],line,MAXLINE);
puts(line);
}
else{
sleep(2);
close(fd[0]);
printf("parent process writing into pipe\n");
write(fd[1],"helllo\n",6);
}
return 0;
}
