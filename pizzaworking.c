#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define MIN_PIZZA 0 //TDefine minimum amount of pizza required
#define MAX_PIZZA 5 //It uses 12 threads to do the count
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int pizzaCount = 0;

void * controlPizza(void *arg){
    for(;;){
        if (pizzaCount > MIN_PIZZA){
            pthread_mutex_lock (&mutex);
            pizzaCount--;
            printf("User eats Pizza\n");
            printf("Remaining Pizza: %d\n", pizzaCount);
            pthread_mutex_unlock (&mutex);
            sleep(2);
        }

        if (pizzaCount < MAX_PIZZA){
            pthread_mutex_lock (&mutex);
            pizzaCount++;
            printf("Chef makes Pizza\n");
            printf("Remaining Pizza: %d\n", pizzaCount);

            pthread_mutex_unlock (&mutex);
            sleep(2);
        }
    }
}


int main(void){
    int i=0;
    pthread_t *thread_group = malloc(sizeof(pthread_t) * 100); //create a thread group the size of THREADS
    for (i=0; i<2; ++i){
        pthread_create(&thread_group[i], NULL, controlPizza, NULL); //Start all threads to begin work
    }

    for (i=0; i<2; ++i){
        pthread_join(thread_group[i], NULL); // wait for all threads to finish
    }
  return EXIT_SUCCESS;
}