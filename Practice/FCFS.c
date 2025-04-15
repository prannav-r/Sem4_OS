#include <stdio.h>

// FCFS

void findwt(int n, int bt[], int wt[])
{
    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }
}

void findtat(int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgt(int processes[], int n, int bt[])
{
    int wt[n], tat[n];
    findwt(n, bt, wt);
    findtat(n, bt, wt, tat);

    int twt = 0, ttat = 0;
    for (int i = 0; i < n; i++)
    {
        twt += wt[i];
        ttat += tat[i];
    }
    // Display processes along with all details
    printf("Processes   Burst time   Waiting time   Turn around time\n");

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        printf("   %d ", (i + 1));
        printf("       %d ", bt[i]);
        printf("       %d", wt[i]);
        printf("       %d\n", tat[i]);
    }

    float(avgwt) = (float)twt / (float)n;
    float(avgtat) = (float)ttat / (float)n;
    printf("Average waiting time = %f", avgwt);
    printf("\n");
    printf("Average turn around time = %f ", avgtat);
}

int main()
{
    int i, n;
    printf("Enter the Number of Processes:");
    scanf("%d", &n);

    int processes[n];
    int bt[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter the Process No:");
        scanf("%d", &processes[i]);
        printf("Enter the Burst Time:");
        scanf("%d", &bt[i]);
    }
    findavgt(processes, n, bt);
}