#include <stdio.h>

int main()
{
    int A[100][4]; // [Process ID, Burst Time, Waiting Time, Turnaround Time]
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;
    }

    // Sort processes by Burst Time (SJF logic)
    for (i = 0; i < n; i++)
    {
        index = i;
        for (j = i + 1; j < n; j++)
        {
            if (A[j][1] < A[index][1])
                index = j;
        }

        // Swap burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        // Swap process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    A[0][2] = 0; // First process waiting time is 0

    // Calculate waiting times
    for (i = 1; i < n; i++)
    {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
        {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }

    avg_wt = (float)total / n;
    total = 0;

    // Print table header
    printf("\nP\tBT\tWT\tTAT\n");

    // Calculate turnaround time and print details
    for (i = 0; i < n; i++)
    {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        printf("P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    avg_tat = (float)total / n;

    // Print averages
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
