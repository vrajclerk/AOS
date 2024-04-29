//Client server application using pipes: Client sends file name to server and server sends file content or error as reply to client’s request.
#include<stdio.h>
#include<unistd.h>

int main(){
  int pipefd1[2],pipefd2[2];
  int returnstatus1,returnstatus2;
  int pid;
  int rad; //define rad to store radius
  int area; //define area to store area

  returnstatus1=pipe(pipefd1);

  if(returnstatus1==-1){
    printf("Unable to create pipe 1");
    return 1;
  }
  returnstatus2=pipe(pipefd2);
  if(returnstatus2==-1){
    printf("Unable to create pipe 2");
    return 1;
  }
  pid=fork();

  if(pid!=0){
    close(pipefd1[0]); //close read end of  unwanted pipe 1
    close(pipefd2[1]); //close write end of unwanted pipe 2
    printf("Enter radius of circle: ");
    scanf("%d",&rad); //read radius from user
  printf("In Parent: Writing to server radius – is %d\n", rad);
    
      write(pipefds1[1], &rad, sizeof(rad)); // Write radius to pipe
    
      read(pipefds2[0], &area, sizeof(area)); // Read area from pipe
    
      printf("In Parent: Reading from server – Area is %d\n", area);
    
   } else { //child process
      close(pipefds1[1]); // Close the unwanted pipe1 write side
    
      close(pipefds2[0]); // Close the unwanted pipe2 read side
    
      read(pipefds1[0], &rad, sizeof(rad)); // Read radius from pipe
    
      area = 3.14 * rad * rad; // Calculate area
      printf("In Child: Reading from client – radius is %d\n", rad);
      printf("In Child: Writing to client – area is %d\n", area);
      write(pipefds2[1], &area, sizeof(area)); // Write area to pipe
   }
   return 0;
}