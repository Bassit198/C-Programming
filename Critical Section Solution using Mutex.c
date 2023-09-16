/*
Name: Bassit Ilahi

Panther ID: 6328318

Description: This program uses mutex locks for 2 threads to provide a solution to the critical section problem.

Certification: I, Bassit Ilahi, certify that the submitted documents belongs to me and is the work of no other individual or sources. 
I certify that this work is my own and was not plagiarized or replicated by any means. 
I affirm that this work does not fall into the category of plagiarism as per abiding to FIU's guidelines and policies relating to plagiarism.

Reference: Some skeleton code was provided by the instructor. The provided code was meant as a guide to follow as per intructions. Aside from 
the provided code, the remaining code and implementation was done by myself with no third party help. Additionally, the notes provided in 
module 5 and 6 were used as references for implementing idea.  

Task 2: 
- entry section is commented in code blow
- critical section is commented in code below
- exit section is commented in the code below
- remainder section is all code that are not in entry, critical and exit section in code below

This implementation is a solution to critical section problem because it satisfies the below mentioned conditions necessary for solution 
to critical section:
1. Bounded Waiting: this is achieved by the use of mutex locks since the mutex locks will only allow one section to access the critical 
section exclusively. If another portion of code is trying to enter the critical section, it will check if there is any mutex lccks on 
the critical section. If there is a mutex lock, it will wait until the lock is released. This condition is stated in the entry section of 
both threads. By using mutex locks, starvation of a process is avoided.

2. Mutual Exclusion: This is achieved by the mutex locks also. This will ensure only one process (thread) can modify the shared counter 
variable and then after this modification is done, the lock is released for another process to aquire that lock. 

3. Progress: The progress for each thread is defined by the the loop running for MAX_UPDATES times. Each time this loop runs, the thread 
increments the counter->value variable in the critical section. This condition for critical section solution allows each thread to execute 
a modification on counter->value until MAX_UPDATES and each increment is tracked by variable i which is incremented by 1 each loop until 
MAX_UPDATES.

Summary: 
Bounded waiting: achieved by mutex locks causing each thread to have a finite waiting time and critical section is shared fairly to prevent starvation.
Mutual Exclusion: thread acquire a lock before entering critical section to prevent other threads from accessing critical section simultaneously.
Progress: loop to MAX_UPDATES causes modification of critical section until limit is reached.

*/

//imported libraries
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_UPDATES 2000000

/* Struct a shared variable to store result */
struct shared_data {
    int value;
    int bonus_count;
};

/* Global shared variable */
struct shared_data *counter;

/* Mutex lock */
pthread_mutex_t mutex;

/* Thread1 function */
void *thread1() {
    int i = 0;
    while (i < MAX_UPDATES) {
        /* Entry section */
        if (pthread_mutex_lock(&mutex) == 0) {

			/* Critical section */
			counter->value++;

			// check to verify if bonus is required 
			if (counter->value % 100 == 0) {
				counter->bonus_count++;
			}

			/* Exit section */
			// unlock mutex lock
			pthread_mutex_unlock(&mutex);
			
			//increment i on every loop so that while loop can run again 
			i++;
		}
    }

    printf("Im thread1, I did %d updates and I got the bonus for %d times, counter = %d\n", i, counter->bonus_count, counter->value);
    return NULL;
}


/* Thread2 function */
void *thread2() {
    int i = 0;
    while (i < MAX_UPDATES) {
        /* Entry section */
        if (pthread_mutex_lock(&mutex) == 0) {

			/* Critical section */
			counter->value++;

			/* Exit section */
			// unlock mutex locks
			pthread_mutex_unlock(&mutex);

			//increment i on every loop so that while loop can run again 
			i++;
		}
    }

    printf("Im thread2, I did %d updates, counter = %d\n", i, counter->value);
    return NULL;
}


int main() {
	pthread_t tid[2];
	int rc;
	
	/* Allocate memory for shared data */
	counter = (struct shared_data *) malloc(sizeof(struct shared_data));
	counter->value = 0;
	
	/* Initialize mutex lock */
	if ((pthread_mutex_init(&mutex, NULL))) {
		printf("Error occured when initialize mutex lock.");
	exit(0);
	}
	
	/* Required to schedule thread independently */
	pthread_attr_t attr;
	if ((pthread_attr_init(&attr))) {
		printf("Error occured when initialize pthread_attr_t.");
	exit(0);
	}
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	
	/* Create thread1 */
	if ((rc = pthread_create(&tid[0], &attr, thread1, NULL))) {
		fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
		exit(0);
	}
	
	/* Create thread2 */
	if ((rc = pthread_create(&tid[1], &attr, thread2, NULL))) {
		fprintf(stderr, "ERROR: pthread_create, rc: %d\n", rc);
		exit(0);
	}
	
	/* Wait for threads to finish */
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	
	//print parent counter
	printf("from parent counter = %d\n", counter->value);
	
	/* Clean up */
	pthread_mutex_destroy(&mutex);
	free(counter);
	pthread_exit(NULL);
	
	return 0;
}
