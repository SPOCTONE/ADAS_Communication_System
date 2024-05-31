#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore; // semaphore variale declaration in global space
int* flags; // declaring an integer pointer to store the flags 

void* BSD() {
	char choice;
	static int count = 0; // static variable to keep track of the number of times the function is called
	
	sem_wait(&semaphore); // s=0
	
	printf("Is the camera %d detecting any vehicles? Press Yes (Y) or No (N)\n", ++count);
	scanf(" %c", &choice);
	if(choice== 'y' || choice== 'Y') { // if the camera is detecting an obstacle
		*flags=1;
		flags++;	
	}
	else {
		*flags=0;
		flags++;
	}

	/*
    if(count==3) {
		execl("/home/sys1/Project/BSDalert", "BSDalert", NULL);
	}
	*/

	sem_post(&semaphore); // s=1
}

int main()
{	
	key_t key = ftok("shmfile", 13); // generating an IPC key
	int shmid = shmget(key, 64, 0666 | IPC_CREAT); 
	// allocating a shared memory segment and storing the identifier in shmid
	flags = shmat(shmid, 0, 0); 
	// attaching the shm segment associated with the shmid and returning it's starting address
	
	pthread_t cam1, cam2, cam3;
	sem_init(&semaphore,0,1); // initiating a binary semaphor
	
	pthread_create(&cam1, NULL, BSD, NULL); // creating the threads
	pthread_create(&cam2, NULL, BSD, NULL);
	pthread_create(&cam3, NULL, BSD, NULL);
	
	pthread_join(cam1, NULL); // waiting for the threads to terminate
	pthread_join(cam2, NULL);
	pthread_join(cam3, NULL);
	
	sem_destroy(&semaphore); // destroying the semaphore
	pthread_exit(NULL); // exiting the thread

	shmdt(flags); // detaching the shared memory segment
	return 0;
}
