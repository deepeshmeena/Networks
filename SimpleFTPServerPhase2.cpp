#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define PORT 2024
extern int errno;
int main (int argc, char const *argv[]){
  struct sockaddr_in server;
  struct sockaddr_in from;  
  int sd;
//checking if correct number of arguments are given on the command line
if(argc != 2 ) {  fprintf(stderr, "%s", "wrong command line arguments\n");    
			exit(1);					

}
int PORT = strtol(argv[1], NULL, 10);

  sd = socket (AF_INET, SOCK_STREAM, 0);
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));

  server.sin_family = AF_INET;  
  server.sin_addr.s_addr = htonl (INADDR_ANY);
  server.sin_port = htons (PORT);

   if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1){
      
        fprintf(stderr, "%s", "Bind Failed\n");    
			exit(2);
    
  }

  else {printf("BindDone: %s\n", argv[1]);}



  if (listen (sd, 5) == -1){
      printf("Failed to listen\n");
        return -1;
  }

else {   printf("ListenDone: %s\n", argv[1]);

}



 while (1){
      int client;
      int length = sizeof (from);
      //printf ("connect to port :  %d...\n",PORT);
      fflush (stdout);

      ////here I made some changes
      client = accept (sd, (struct sockaddr *) &from, (socklen_t*)&length);  
      ///
      if (client < 0)
         continue;
      char file[100];

      read (client, file, 100) <= 0;
      printf("FileRequested: %s\n", file);  
      //

//////////////////////////

//check if file exits or not 
if( access( file, F_OK ) == -1 ) {
    
printf("FileTransferFail\n");
fprintf(stderr, "%s", "The file you requested is not present\n"); 
return -1;
} 


/////////////////
        FILE *fl = fopen(file, "r");
        char text[500]; //your file size
        int len = 0;
        char c;
/////////////////





//////////////////////
        while((c = fgetc(fl)) != EOF){
            text[len] = c;
            len++;    
        }
        text[len] = '\0';
printf("TransferDone: %d bytes\n",len);
        //printf("%d", len);
        //printf("%s", text);
        write(client, &len, 4);
        write(client, text, len);
      close (client);
    }       
}       
