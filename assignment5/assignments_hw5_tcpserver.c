#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

void error(char *msg) {
  perror(msg);
  exit(1);
}

int authenticate(char *passwd){
  unsigned char auth = 0;
  char buf[512];

  if(strncmp(passwd,"letmein",7)==0)
        auth=1;
  else
        auth=0;

  strcpy(buf,passwd);
  if (auth==1){
        printf(" Authentication Success\n");
        return 1;
  }
  else{
        printf("The following password is incorrect: %s", buf);
        return 0;
  }
}

int main(int argc, char **argv) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */

  portno = atoi("8888");

  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0)
    error("ERROR opening socket");

  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,
             (const void *)&optval , sizeof(int));

  bzero((char *) &serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;

  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  serveraddr.sin_port = htons((unsigned short)portno);

  if (bind(parentfd, (struct sockaddr *) &serveraddr,
           sizeof(serveraddr)) < 0)
    error("ERROR on binding");

  if (listen(parentfd, 5) < 0)
    error("ERROR on listen");

  clientlen = sizeof(clientaddr);
  while (1) {

    childfd = accept(parentfd, (struct sockaddr *) &clientaddr, &clientlen);
    if (childfd < 0)
      error("ERROR on accept");

    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                          sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server established connection with %s (%s)\n",
           hostp->h_name, hostaddrp);

    bzero(buf, BUFSIZE);
    n = read(childfd, buf, BUFSIZE);
    if (n < 0)
      error("ERROR reading from socket");
    printf("server received %d bytes: %s", n, buf);

    authenticate(buf);

    close(childfd);
  }
}
              
