// transferclient.c
#include <stdio.h>	
#include <string.h>	
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <stdlib.h>
int main(int argc , char **argv)
{
  // argv[1]: IP address
  // argv[2]: port
  // argv[3]: file name
  if (argc != 4) { return EXIT_FAILURE; }
  int sock;
  sock = socket(AF_INET , SOCK_STREAM , 0);
  if (sock == -1) { return EXIT_FAILURE; } 
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  int port = strtol(argv[2], NULL, 10);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  int rtv = connect(sock, (struct sockaddr *) &server, sizeof(server));
  if (rtv < 0) { return EXIT_FAILURE; }
  FILE * fptr = fopen(argv[3], "r");
  if (fptr == NULL) { return EXIT_FAILURE; }
  fseek(fptr, 0, SEEK_END);  // go to the end of the file
  long length = ftell(fptr); // find the file's length
  fseek(fptr, 0, SEEK_SET);
  unsigned char message[1024];
  // convert the long integer into eight bytes in message
  long lengthtemp = length;
  for (int cnt = 0; cnt < 8; cnt ++)
    {
      message[cnt] = lengthtemp & 0XFF;
      printf("message[%d] = %d\n", cnt, message[cnt]);
      lengthtemp >>= 8;
    }
  rtv = write(sock, message, 8);
  if (rtv != 8)
    {
      printf("write 8 bytes fail\n");
      return EXIT_FAILURE;
    }
  printf("length = %ld\n", length);
  int freadlen;
  int sendlen;
  while (length > 0)
    {
      if (length > 1024)
	{ freadlen = fread(message, sizeof(unsigned char), 1024, fptr); }
      else
	{ freadlen = fread(message, sizeof(unsigned char), length, fptr); }
      if (freadlen == EOF)
	{
	  printf("Error, unexpected EOF\n");
	  close (sock);
	  fclose (fptr);
	  return EXIT_FAILURE; 
	}
      sendlen = write(sock, message, freadlen);
      if (sendlen < 0) 
	{
	  printf("Error, write fail\n");
	  close (sock);
	  fclose (fptr);
	  return EXIT_FAILURE; 
	}
      if (freadlen != sendlen)
	{ printf("freadlen = %d, sendlen = %d\n", freadlen, sendlen); }
      length -= sendlen;
    }
  close(sock);
  fclose(fptr);
  return EXIT_SUCCESS;
}

