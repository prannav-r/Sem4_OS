#include <stdio.h>

int main()
{
    int n, i, time_quantum, total = 0;
    int bt[10], rt[10], wt[10], tat[10], at[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Burst Time and Arrival Time
    for (i = 0; i < n; i++)
    {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Copy burst time to remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    int completed = 0, t = 0;
    while (completed < n)
    {
        int done = 1;
        for (i = 0; i < n; i++)
        {
            if (rt[i] > 0 && at[i] <= t)
            {
                done = 0;
                if (rt[i] > time_quantum)
                {
                    t += time_quantum;
                    rt[i] -= time_quantum;
                }
                else
                {
                    t += rt[i];
                    wt[i] = t - at[i] - bt[i]; // Waiting time
                    tat[i] = t - at[i];        // Turnaround time
                    rt[i] = 0;
                    completed++;
                }
            }
        }

        if (done)
            t++;
    }

    // Output
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
