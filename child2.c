#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "func.h"

int main(int argc, char *argv[])
{

    MaxAndAvg maxAndAvg;
    int lengthSub = atoi(argv[1]);

    int subArr[lengthSub];

    wait(NULL);

    if (read(STDIN_FILENO, subArr, sizeof(int) * lengthSub) < 0)
    {
        return 9;
    }

    if (strcmp(argv[2], "MAX-AVG") == 0)
    {
        maxAndAvg.avg = getAvg(subArr, lengthSub);
        maxAndAvg.max = getMax(subArr, lengthSub);
    }
    else if (strcmp(argv[2], "MAX") == 0)
    {
        maxAndAvg.max = getMax(subArr, lengthSub);
    }
    else if (strcmp(argv[2], "AVG") == 0)
    {
        maxAndAvg.avg = getAvg(subArr, lengthSub);
    }

    if (write(STDOUT_FILENO, &maxAndAvg, sizeof(MaxAndAvg)) < 0)
    {
        return 9;
    }

    return 0;
}
