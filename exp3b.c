//Write a program that uses fork() and assign some different task to child process. And make sure that parent exits after child finishes its task. 
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
  int a=fork();

  if(a<0){
    printf("child not created");
    
  }
  else if(a==0){
    printf("child process\n");
    printf("child processID:%d\n",getpid());
    printf("child parent  processID:%d\n",getppid());
    sleep(5); //parent pachi child execute karva mate
    printf("child Terminated\n");
  }
  else{
    printf("parent process\n");
    printf("parent ID:%d\n",getpid());
    printf("parent parent processID:%d\n",getppid());
    //wait(NULL); //child pachi parent execute karva mate
    //sleep(5);
    printf("parent Terminated\n");
  }
}
