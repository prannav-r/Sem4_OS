#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

#define LEFT(phnum) ((phnum + N - 1) % N)
#define RIGHT(phnum) ((phnum + 1) % N)

int state[N];
int phil[N] = {0, 1, 2, 3, 4};
sem_t mutex;
sem_t S[N];

void test(int phnum)
{
    if (state[phnum] == HUNGRY && state[LEFT(phnum)] != EATING && state[RIGHT(phnum)] != EATING)
    {
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes forks %d and %d\n", phnum + 1, LEFT(phnum) + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", phnum + 1, LEFT(phnum) + 1, phnum + 1);
    printf("Philosopher %d is Thinking\n", phnum + 1);
    test(LEFT(phnum));
    test(RIGHT(phnum));
    sem_post(&mutex);
}

void *philosopher(void *num)
{
    int *i = num;
    while (1)
    {
        sleep(1); // thinking
        take_fork(*i);
        sleep(2); // eating
        put_fork(*i);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is Thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}
