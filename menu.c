#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main() {
  int choice;
  printf("Welcome to the Advanced Driver Assistance System (ADAS) menu\n");
  while (1) { // infinite loop
    printf("\nADAS modules\n\n 1. Collision Avoidance System (CAS)\n 2. Lane Departure Warning (LDW)\n 3. Adaptive Cruise Control (ACC)\n 4. Automatic Emergency Braking (AEB)\n 5. Blind Spot Detection (BSD)\n 6. Exit\n\nEnter your choice : ");
    scanf("%d", &choice);
    printf("\n");
    
    switch (choice) {
    case 1: // CAS
      //execl("/home/sys1/Project/CAS", "CAS", NULL);
      system("./CASinput");
      break;

    case 2: // LDW
      //execl("/home/sys1/Project/LDW", "LDW", NULL);
      system("./LDW");
      break;

    case 3: // ACC
      //execl("/home/sys1/Project/ACC", "ACC", NULL);
      system("./ACCsend");
      system("./ACCreceive");
      break;

    case 4: // AEB
      //execl("/home/sys1/Project/AEBclient", "AEBclient", NULL);
      system("./AEBclient");
      break;

    case 5: // BSD
      //execl("/home/sys1/Project/BSD", "BSD", NULL);
      system("./BSDinput");
      system("./BSDalert");
      break;

    case 6: //exiting
      printf("Program Terminated Sucessfully\n");
      exit(1);

    default:
      printf("Enter a valid number (1 to 6)\n");
    }
  }

  return 0;
}

