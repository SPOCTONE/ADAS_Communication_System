#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct collision {
  char choice;
  uint8_t camNum[4];
  float dist[4];
  float speed;
} car;

int main(){
  key_t key = ftok("shmfile", 13);
  uint32_t shmid = shmget(key, 1024, 0666 | IPC_CREAT);
  car *ptr = (car *)shmat(shmid, NULL, 0);
  
  char buff[1024];

  int port = 8080;
  char *ip = "127.0.0.1";

  struct sockaddr_in server_addr, client_addr; 
  socklen_t addr_size;

  // Using the socket(int domain, int type, int protocol) function to create a socket.
  int sockfd = socket(AF_INET,SOCK_DGRAM, 0);
  if (sockfd < 0){
    perror("[-]socket error");
    exit(1);
  }

  memset(&server_addr, '\0', sizeof(server_addr));
  // Internet Protocol selected
  server_addr.sin_family = AF_INET;
  // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
  server_addr.sin_port = htons(port);
  // This inet_addr() function converts the Internet host address server_ip from IPv4 numbers-and-dots notation into binary data in network byte order.
  server_addr.sin_addr.s_addr = inet_addr(ip);

  int n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0) {
    perror("[-]bind error");
    exit(1);
  }

  bzero(buffer, 1024);
  addr_size = sizeof(client_addr);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
  printf("[+]Data received: %s\n", buffer);

  bzero(buffer, 1024);
  strcpy(buffer, "Hi from the UDP server");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, addr_size);
  printf("[+]Data sent: %s\n", buffer);
  
  bzero(buffer, 1024);
  gcvt(ptr->speed, 6, buffer);
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, addr_size);
  printf("[+]Data sent: %s\n", buffer);
  
  return 0;
}