#include <stdio.h>
#include "common.h"
#include <pthread.h>

//#include "mythreads.h"

int done = 0;

void* worker(void* arg) {
    printf("this should print first\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
   // pthread_create(&p, NULL, worker, NULL);
   // while (done == 0)
	;
    printf("this should print last\n");
    return 0;
}
