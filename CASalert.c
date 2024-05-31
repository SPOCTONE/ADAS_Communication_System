#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/shm.h>
#include <unistd.h>

typedef struct collision { // structure for sharing data between CAS.c and CASalert.c
  char choice;
  uint8_t camNum[4];
  float distance[4];
  float speed;
} car;

int main() {

  key_t key = ftok("shmfile", 13); // ftok to generate unique key
  uint8_t shmid = shmget(key, 1024, 0666 | IPC_CREAT); // shmget returns an identifier in shmid
  car *receive = (car *)shmat(shmid, NULL, 0); // shmat to attach to shared memory

  printf("Data read from shared memory\n");

  char *camDir[] = {"front", "left", "right", "back"};

  if (receive->choice == 'y' || receive->choice == 'Y') { // if the cameras are detecting an obstacle

    float thresholdDistance = 2 * (receive->speed / 3.6); // threshold distance = 2 * speed in m/s
    printf("\nThreshold distance is %.2f meters\n\n", thresholdDistance);

    for (uint8_t i = 0; i < 4; i++) { // looping through each of the 4 cameras

      if (receive->camNum[i] == 1) { // if the camera is detecting an obstacle
        printf("Distance from camera %d at the %s: %.2f meters\n", i + 1, camDir[i], receive->distance[i]);

        if ((receive->distance[i] < thresholdDistance) && i!=3) { // if the distance is less than the threshold distance
          printf("Alert! Collision may occur in the field of view of camera %d at the %s\n\n", i + 1, camDir[i]);
          execl("CASclient", "CASclient", NULL);
        } 
        else if((receive->distance[i] < thresholdDistance) && i==3) { // If the back camera has an obstacle in the blind spot we dont want the car to stop
          printf("Alert! Collision may occur in the field of view of camera %d at the %s\n\n", i + 1, camDir[i]);
        } 
        else {
          printf("You're good to go\n\n");
        }
      }
    }
  } 
  else {
    printf("You're good to go\n\n");
    execl("menu", "menu", NULL);
  }

  shmdt(receive);
  return 0;
}