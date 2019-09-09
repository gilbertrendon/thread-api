#include <stdio.h>
#include <pthread.h>

//#include "mythreads.h"

int balance = 0;

pthread_mutex_t lock;

void* worker(void* arg) {
    pthread_mutex_lock(&lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&lock, NULL);

    pthread_t p;
    pthread_create(&p, NULL, worker, NULL);

    pthread_mutex_lock(&lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&lock);

    pthread_join(p, NULL);
    return 0;
}
