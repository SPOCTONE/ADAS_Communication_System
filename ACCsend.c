#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

typedef struct car {
  float speed;
  float distance;
} ACC;

int main() {
  int msgid; // message queue id
  ACC sender; // structure variable containing the speed and distance of our car to be sent as a message
  printf("Sender Function:\n"); 
  
  if ((msgid = msgget((key_t)13, 0666 | IPC_CREAT)) == -1) { // create message queue
    perror("msgsnd");
  }

  printf("Enter the current speed of our car (in kmph):\n");
  scanf("%f", &sender.speed);

  printf("Enter the distance between us and the car in front (in metres) :\n");
  scanf("%f", &sender.distance);
  
  if (msgsnd(msgid, (void *)&sender, 0, 0) == -1) { // send message to the queue
    perror("msgsnd");
  }
  
  // execl("/home/sys1/Project/ACCreceive", "ACCreceive", NULL);
  return 0;
}
