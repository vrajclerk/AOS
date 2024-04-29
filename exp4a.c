//Implement file copy command using system call also handle all possible errors. 
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 4096

int main(){
   char s[100];
  char d[100];
  printf("source file name:");
  scanf("%s",s);

  int source_fd = open(s,O_RDONLY);
  if(source_fd==-1){
    printf("source file not found");
    return 1;
  }
  int destination_fd = open("destination.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);

  if(destination_fd==-1){
    printf("destination file not found");
    close(source_fd);
    return 1;
    
  }
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  while((bytes_read=read(source_fd,buffer,BUFFER_SIZE))>0){
    if(write(destination_fd,buffer,bytes_read)!=bytes_read){
      printf("error writing to destination file");
      close(source_fd);
      close(destination_fd);
      return 1;
    }
  }
  close(source_fd);
  close(destination_fd);
  printf("file copied successfully");

  return 0;
}
  