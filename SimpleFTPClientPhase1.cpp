#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    
int byte_count=0;
int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

if(argc != 3 ) {  fprintf(stderr, "%s", "wrong command line arguments\n");    
			exit(1);					

}

char *first_argument = strdup(argv[1]);
//printf("%s\n",first_argument);
char *filename = strdup(argv[2]);

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
    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); // port
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
printf("ConnectDone: %s\n", argv[1]);   

//    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
  //  {
    //     fprintf(stderr, "%s", "server connect failed\n");    
	//		exit(1);
      
    //}

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen(filename, "ab"); 
    if(NULL == fp)
    {
        fprintf(stderr, "%s", "error opening file\n");    
			exit(3);
    }

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sockfd, recvBuff, 256)) > 0)
    {
   //     printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
byte_count +=bytesReceived;
    }

  //  if(bytesReceived < 0)
    //{
      //  printf("\n Read Error \n");
    //}

printf("FileWritten: %d bytes\n", byte_count);   
    return 0;
}

