#include <stdio.h>

int main()
{
    int n = 5; // Number of processes
    int m = 3; // Number of resources

    // Allocation Matrix
    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Max Matrix
    int max[5][3] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    // Available Resources
    int avail[3] = {3, 3, 2};

    int f[n], ans[n], ind = 0;

    // Mark all processes as unfinished
    for (int i = 0; i < n; i++)
        f[i] = 0;

    // Calculate Need Matrix
    int need[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Main logic to find Safe Sequence
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    int safe = 1;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            safe = 0;
            printf("The system is not in a safe state.\n");
            break;
        }
    }

    if (safe)
    {
        printf("The system is in a safe state.\nSafe sequence is:\n");
        for (int i = 0; i < n; i++)
        {
            printf("P%d", ans[i]);
            if (i != n - 1)
                printf(" -> ");
        }
        printf("\n");
    }

    return 0;
}
