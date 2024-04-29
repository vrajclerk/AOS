//producer consumer problem using mutual exclusion
#include<stdio.h>
#include<pthread.h>
#define size 5

int buff[size];
int count=0;
int in=0;
int out=0;
int item = 0;
pthread_mutex_t mutex;

void* producer (void* arg)
{
    for(int i=0;i<10;i++)
    {        pthread_mutex_lock(&mutex);

        while(count==size)
        {
            pthread_mutex_unlock(&mutex);
            printf("Buffer is full\n");
            sleep(1);
            pthread_mutex_lock(&mutex);
        }

        item++;

        buff[in]=item;
        in=(in+1)%size;
        count++;
        printf("Producer produced item %d\n",item);
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void* arg)
{
    for(int i = 0;i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        while(count==0){
            pthread_mutex_unlock(&mutex);
            printf("Buffer is empty\n");
            sleep(1);
            pthread_mutex_lock(&mutex);
        }
        item = buff[out];
        out = (out+1)%size;
        count--;
        printf("Consumer consumed item %d\n",item);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t pro,con;

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&pro,NULL,producer,NULL);
    pthread_create(&con,NULL,consumer,NULL);

    pthread_join(pro,NULL);
    pthread_join(con,NULL);

    pthread_mutex_destroy(&mutex);

return 0;
}