#include<stdio.h>
#include<string.h>

int main(){
  FILE *read_fp;
  FILE *write_fp;
  
  char msg[100];
  
  printf("Client is ready\n");
  printf("\n");
  
  while(1){
  
  printf("client: ");
  fgets(msg,100,stdin);
  
  write_fp=fopen("pipe1","w");
  fprintf(write_fp,"%s",msg);
  fclose(write_fp);
  
   read_fp = fopen("pipe2", "r");
   fgets(msg, 100, read_fp);
   fclose(read_fp);
        
    printf("server: %s",msg);
  
  
  }
  return 0;
  }
