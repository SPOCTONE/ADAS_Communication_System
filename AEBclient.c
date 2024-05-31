#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 4444 // port number

int main() {

  int clientSocket; // client socket descriptor
  struct sockaddr_in serverAddr; // server address structure
  char buffer[1024]; // buffer to store the message from the server

  clientSocket = socket(PF_INET, SOCK_STREAM, 0); // creating the socket 
  printf("[+]Client Socket Created Sucessfully.\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));
  serverAddr.sin_family = AF_INET; // assigning the address family
  serverAddr.sin_port = htons(PORT); // assigning the port number
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // assigning the port number by converting it from host byte order to network byte order

  connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); // connecting to the server socket 
  printf("[+]Connected to Server.\n\n");

  recv(clientSocket, buffer, 1024, 0); // receiving the message from the server and storing it in the buffer

  double speed = atof(buffer); // converting the string received to float
  printf("The speed of the car is: %.4lf kmph\n", speed);
  printf("Initiating Emergency Breaking.\n");
  printf("Reducing the speed by 15 feet/s (maximum safe deceleration of a typical car)\n");
  while(speed>0) { //
    sleep(1);
    speed=speed-16.4592;
    if(speed<0) {
    printf("0\n");
    continue;
    }
    printf("%.4lf\n", speed);
  }
  printf("The car has been stopped safely.\n");

  printf("\n[+]Closing the connection.\n");
  return 0;
}
