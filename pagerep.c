#include <stdio.h>

// FIFO

void fifo(int pages[], int n, int frames)
{
    int queue[frames], front = 0, rear = 0, count = 0, faults = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check if page is already in queue
        for (int j = 0; j < count; j++)
        {
            if (queue[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        // If not found, insert page and replace oldest if full
        if (!found)
        {
            if (count < frames)
            {
                queue[rear++] = pages[i];
                count++;
            }
            else
            {
                queue[front] = pages[i];
                front = (front + 1) % frames;
                rear = (rear + 1) % frames;
            }
            faults++;
        }

        // Print current state
        printf("Page %d: ", pages[i]);
        for (int k = 0; k < count; k++)
            printf("%d ", queue[(front + k) % frames]);
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", faults);
}

int main()
{
    int pages[] = {1, 2, 3, 4, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    fifo(pages, n, frames);
    return 0;
}
