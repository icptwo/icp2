// CH25:transferserver.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>	
#include<netdb.h>
#include<time.h>
#include<unistd.h>	
#include<stdbool.h>
#include<sys/socket.h> // socket, socket
#include<arpa/inet.h>	
#include<sys/utsname.h>
int main(int argc , char **argv)
{
  int descptr;
  descptr = socket(AF_INET , SOCK_STREAM , 0); 
  if (descptr == -1) { return EXIT_FAILURE; } 
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0; 
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
  struct sockaddr_in client;
  int client_sock;
  int client_size;
  client_sock = accept(descptr, (struct sockaddr *) &client,
		       (socklen_t*) & client_size);
  if (client_sock < 0) { return EXIT_FAILURE; }
  unsigned char message[1024];
  long length = 0;
  int recvlen = read(client_sock, message, 8); 
  if (recvlen != 8)
    {
      printf("Error, recvlen = %d\n", recvlen);
      close(client_sock);
      return EXIT_FAILURE;
    }
  for (int cnt = 7; cnt >= 0; cnt --)
    {
      length <<= 8;
      length += message[cnt];
      printf("message[%d] = %d, length = %ld\n",
	     cnt, message[cnt], length);
    }
  printf("length = %ld\n", length);
  char * filename = "fromclient";
  FILE * fptr = fopen(filename, "w");
  int readlen;
  int fwritelen;
  if (fptr == NULL) { return EXIT_FAILURE; }
  while (length > 0)
    {
      if (length > 1024)
	{ readlen = read(client_sock, message, 1024); }
      else
	{ readlen = read(client_sock, message, 1024); }
      if (readlen < 0)
	{
	  printf("Error, readlen < 0\n");
	  close (client_sock);
	  fclose (fptr);
	  return EXIT_FAILURE; 
	}
      fwritelen = fwrite(message, sizeof(unsigned char), readlen, fptr);
      if (fwritelen < 0) 
	{
	  printf("Error, fwrite fail\n");
	  close (client_sock);
	  fclose (fptr);
	  return EXIT_FAILURE; 
	}
      if (fwritelen != readlen)
	{ printf("fwritelen = %d, readlen = %d\n", fwritelen, readlen); }
      length -= readlen;
    }
  close(client_sock);
  fclose(fptr);
  return EXIT_SUCCESS;
}
