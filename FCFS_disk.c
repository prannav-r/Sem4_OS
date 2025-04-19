#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, i;
    int seek = 0;

    // Example input: 8 requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter the disk requests (track numbers):\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d -> ", request[i]);
        seek += abs(request[i] - head);
        head = request[i];
    }

    printf("END\n");
    printf("Total Seek Time: %d\n", seek);
    printf("Average Seek Time: %.2f\n", (float)seek / n);

    return 0;
}
