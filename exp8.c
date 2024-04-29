#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;


void produce(int item) {

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    printf("Produced item: %d , By : %d\n", item,(int)pthread_self());
}

int consume() {

    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("Consumed item: %d By : %d\n", item,(int)pthread_self());
    return item;
}

void* producer() {

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sem_wait(&empty);
        sem_wait(&mutex);



        produce(i);

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumer() {

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sem_wait(&full);
        sem_wait(&mutex);

        consume();

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {



    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

  pthread_t producer_thread1, consumer_thread1;
  pthread_create(&producer_thread1, NULL, producer, NULL);
  pthread_create(&consumer_thread1, NULL, consumer, NULL);

  pthread_join(producer_thread1, NULL);
  pthread_join(consumer_thread1, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}