#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// This function is executed by each thread
void *printThread(void *threadid) {
    long tid;
    tid = (long)threadid;
    
    printf("thread-%ld running\n", tid + 1);
    printf("thread-%ld closed\n", tid + 1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        // Create a new thread
        rc = pthread_create(&threads[t], NULL, printThread, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        
        // Wait for the current thread to finish before starting the next one
        pthread_join(threads[t], NULL);
    }
    
    // Exit the main thread
    pthread_exit(NULL);
    return 0;
}
