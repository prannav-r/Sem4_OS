#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg)
{
    int threadId = *((int *)arg);
    printf("Thread %d!\n", threadId);
    pthread_exit(NULL);
}

int main()
{
    int numThreads = 5;
    pthread_t threads[numThreads];
    int threadIds[numThreads];

    for (int i = 0; i < numThreads; i++)
    {
        threadIds[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, (void *)&threadIds[i]) != 0)
        {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
    return 0;
}