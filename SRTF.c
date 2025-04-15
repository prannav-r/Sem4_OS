#include <stdio.h>
#include <limits.h>

struct Process
{
    int pid;
    int bt;  // Burst time
    int art; // Arrival time
};

// Function to find waiting time
void findWaitingTime(struct Process proc[], int n, int wt[])
{
    int rt[n]; // Remaining time
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0)
        {
            complete++;
            check = 0;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++;
    }
}

// Function to find Turn Around Time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to find and print all times
void findavgTime(struct Process proc[], int n)
{
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    printf("\nProcesses  Burst Time  Arrival Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].art, wt[i], tat[i]);
    }

    float avgwt = (float)total_wt / n;
    float avgtat = (float)total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avgwt);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat);
}

// Driver code
int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID: ");
        scanf("%d", &proc[i].pid);
        printf("Enter Burst Time: ");
        scanf("%d", &proc[i].bt);
        printf("Enter Arrival Time: ");
        scanf("%d", &proc[i].art);
    }

    findavgTime(proc, n);
    return 0;
}
