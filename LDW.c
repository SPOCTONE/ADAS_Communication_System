#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// function to handle lane deviation signals
void laneDeviation(int signo) { 
  if (signo == SIGINT) // if signal is SIGINT
  { 
    printf("\nALERT! lane deviation detected.\n"); // printing alert message in case of lane deviation
    exit(EXIT_SUCCESS); 
  } 
  else if (signo == SIGQUIT) // if signal is SIGQUIT
  { 
    printf("\nNo lane change observed.\n"); // printing message in case of no lane change
    exit(EXIT_SUCCESS);
  }
}

int main() {
  printf("Are you cruising in your lane?\n"); 
  printf("press Control-C if you are deviating from the lane or Control-\\ if you're not.\n");

  signal(SIGINT, laneDeviation); // registering signal handler for SIGINT
  signal(SIGQUIT, laneDeviation); // registering signal handler for SIGQUIT
  
  if (signal(SIGINT, laneDeviation) == SIG_ERR) // if signal handler for SIGINT is not registered
  {
    fprintf(stderr, "cannot handle SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGQUIT, laneDeviation) == SIG_ERR) // if signal handler for SIGQUIT is not registered
  {
    fprintf(stderr, "cannot handle SIGQUIT!\n");
    exit(EXIT_FAILURE);
  }

  while (1); // infinite loop
  return 0;
}
