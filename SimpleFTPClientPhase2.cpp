#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <string.h>
#include <arpa/inet.h>
extern int errno;
int port;
int main (int argc, char *argv[]){
  int sd;   
  struct sockaddr_in server;

  if(argc != 3 ) {  fprintf(stderr, "%s", "wrong command line arguments\n");    
			exit(1);					

}
//////////////////////////////////////////////

char *first_argument = strdup(argv[1]);
//printf("%s\n",first_argument);
char *file = strdup(argv[2]);

//extract port and ip address from first argument


int c;
//char *first_argument = strdup(argv[1]);

for(int i = 0; first_argument[i] != '\0'; i++) {

if(first_argument[i]==':') c=i;
   
}


char *ip = (char*) malloc(c+1);
char *tto = (char*) malloc(c+1);
strncpy(ip, first_argument, c);
strncpy(tto, first_argument+c+1, c);


//printf("%s\n",ip);
//printf("%s\n",tto);

int port = atoi(tto);

//printf("%d\n",port);


////////////////////////////////








/////////////////////////////////////////
  //port = atoi (argv[2]);
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1){
      perror ("socket() error.\n");
      return errno;
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_port = htons (port);
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1){
      fprintf(stderr, "%s", "server connect failed\n");    
			exit(2);
  }
else printf("ConnectDone: %s\n", argv[1]);  
  //char file[100]; 

///////////////////////////
 // printf("Give me filename: ");
  //fflush(stdout);
 // scanf("%s", file);
///////////////////////
if (write (sd, file, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   int len;
   char text[500];
   read(sd, &len, 4);
   read(sd, text, len);
   //printf("%s\n", text);
   FILE *fl = fopen(file, "w");
if(NULL == fl)
    {
        fprintf(stderr, "%s", "error opening file\n");    
			exit(3);
    }
printf("FileWritten: %d bytes\n",len );
   fprintf(fl, "%s", text);
   fclose(fl);
   close (sd);
}
