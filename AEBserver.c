#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 4444 // port number

int main() {

  int serverSocket; // server socket descriptor
  struct sockaddr_in serverAddr; // server address structure

  int newSocket;
  struct sockaddr_in newAddr;

  socklen_t addr_size; // address size variable to be used in accept() call
  char buffer[1024];

  serverSocket = socket(AF_INET, SOCK_STREAM, 0); // creating the socket
  printf("[+]Server Socket Created Sucessfully.\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET; // assigning the address family
  serverAddr.sin_port = htons(PORT); // assigning the port number by converting it from host byte order to network byte order
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // assigning the IP address

  bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); // binding the socket to the IP address and port number
  printf("[+]Bind to Port number %d.\n", 4444);

  listen(serverSocket, 5); // listening for connections from the client
  printf("[+]Listening...\n");

  newSocket = accept(serverSocket, (struct sockaddr *)&newAddr, &addr_size); // accepting the connection from the client and assigning a new socket descriptor to it

  printf("\nEnter the current speed of the vehicle (in kmph): ");
  scanf("%s", buffer);

  send(newSocket, buffer, strlen(buffer), 0); // sending the message to the client from the new socket descriptor which is the connection with the client socket

  printf("\n[+]Closing the connection.\n");
  return 0;
}
