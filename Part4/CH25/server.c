#include<stdio.h>
#include<stdlib.h>
#include<string.h>	
#include<netdb.h>
#include<time.h>
#include<unistd.h>	
#include<stdbool.h>
#define _BSD_SOURCE // needed for <endian.h>
#include <endian.h>
#include<sys/socket.h> // socket, socket
#include<arpa/inet.h>	
#include<sys/utsname.h>
int main(int argc , char **argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) { return EXIT_FAILURE; }
  int width = 164; // puzzle (81) + common + answer (81) + '\n'
  fseek(fptr, 0, SEEK_END);
  long loc = ftell(fptr);
  int numline = loc / width;
  int descptr;
  descptr = socket(AF_INET , SOCK_STREAM , 0); // IPv4, reliable, single
  if (descptr == -1) { return EXIT_FAILURE; }
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0; // system assigns an available port
  int rtv = bind (descptr, (struct sockaddr *) & server , sizeof(server));
  if (rtv < 0) { return EXIT_FAILURE; }
  // get IP address and port
  struct sockaddr_in serv_addr;
  socklen_t servlen = sizeof(serv_addr);
  rtv = getsockname(descptr, (struct sockaddr *) &serv_addr, & servlen);
  if (rtv < 0) { return EXIT_FAILURE; }
  struct utsname unamestruct;
  uname(& unamestruct);
  struct hostent hostentry;
  struct hostent * hostptr = & hostentry;
  hostptr = gethostbyname(unamestruct.nodename);
  char * hostip = inet_ntoa(*((struct in_addr*)
			      hostptr -> h_addr_list[0]));
  printf("host IP = %s\n", hostip);
  printf("port number %d\n", ntohs(serv_addr.sin_port));
  listen(descptr, 3);
  printf("Server ready\n");
  struct sockaddr_in client;
  char message[1024];
  int client_sock;
  int client_size; 
  client_size = sizeof(struct sockaddr_in);
  srand(time(NULL));
  bool keeprun = true;
  int whichline;
  char oneline[256];
  while (keeprun)
    {
      client_sock = accept(descptr, (struct sockaddr *) &client,
			   (socklen_t*) &client_size);
      if (client_sock < 0) { return EXIT_FAILURE; }
      whichline = rand() % numline;
      fseek(fptr, whichline * width, SEEK_SET);
      fgets(oneline, 164, fptr);
      write(client_sock, oneline, 81);
      int recvlen = recv(client_sock , message , 1024 , 0);
      if (recvlen < 0) { return EXIT_FAILURE; }
      message[recvlen] = '\0'; // end the string
      oneline[163] = '\0';     // replace '\n' by '\0'
      if (strcmp(message, & oneline[82]) == 0)
	{ strcpy(oneline, "Correct"); }
      else
	{ strcpy(oneline, "Wrong"); }
      write(client_sock, oneline, strlen(oneline));
      printf("receive %s\nresult %s\n", message, oneline);
    }
  return EXIT_SUCCESS;
}
