#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int allocation[MAX][MAX]; // Resources currently allocated
int request[MAX][MAX];    // Resources still needed
int available[MAX];       // Available resources
bool finished[MAX];       // Tracks which processes can complete

// Check if a process can finish with available resources
bool canProcessFinish(int process, int num_resources)
{
    for (int j = 0; j < num_resources; j++)
    {
        if (request[process][j] > available[j])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int num_processes, num_resources;

    // Get basic information
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resource types: ");
    scanf("%d", &num_resources);

    // Get available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; i++)
    {
        scanf("%d", &available[i]);
    }

    // Get allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Get request matrix
    printf("Enter request matrix:\n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Initialize all processes as unfinished
    for (int i = 0; i < num_processes; i++)
    {
        finished[i] = false;
    }

    // Try to find a safe execution sequence
    bool progress;
    do
    {
        progress = false;

        // Try each process
        for (int i = 0; i < num_processes; i++)
        {
            if (!finished[i] && canProcessFinish(i, num_resources))
            {
                // Mark process as finished
                finished[i] = true;
                progress = true;

                // Release its resources
                for (int j = 0; j < num_resources; j++)
                {
                    available[j] += allocation[i][j];
                }

                printf("Process %d can finish\n", i);
            }
        }
    } while (progress); // Continue until no more progress is made

    // Check if all processes could finish
    bool deadlock = false;
    printf("\nDeadlocked processes: ");
    for (int i = 0; i < num_processes; i++)
    {
        if (!finished[i])
        {
            deadlock = true;
            printf("%d ", i);
        }
    }

    if (deadlock)
    {
        printf("\nSystem is in deadlock state\n");
    }
    else
    {
        printf("\nNo deadlock detected\n");
    }

    return 0;
}