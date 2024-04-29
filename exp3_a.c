//Print Process ID, Parent process ID, Read user ID, Real group ID, Effective  user ID, effective group ID for current process. 
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
  printf("processID:%d\n",getpid());
  printf("parent processID:%d\n",getppid());
  printf("real user ID: %d\n",getuid());
  printf("real group ID: %d\n",getgid());
  printf("effective user ID: %d\n",geteuid());
  printf("effective group ID: %d\n",getegid());

  
}