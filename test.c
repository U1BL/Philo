#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

void* routine(void *philo)
{
    sleep(1);
    printf("Hello from thread\n");
    return (NULL);
}

int main()
{
    int i = 0;
    pthread_t thread[2];

    while (i < 3)
    {
        if (pthread_create(&thread[i], NULL, &routine, NULL) != 0)
            perror("Failed to create thread");
        pthread_detach(thread[i]);
        i++; 
    }
    i = 0;
    while (i < 3)
    {
        if (pthread_join(thread[i], NULL) != 0)
            perror("Failed to join thread");
        i++;
    }
    pthread_exit(NULL);
}