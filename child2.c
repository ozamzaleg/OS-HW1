#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "definition.h"
#include "communication.h"
#include "func.h"

int main(int argc, char *argv[])
{

    MaxAndAvg maxAndAvg;
    char *massege = argv[2];
    int lengthSub = atoi(argv[1]);

    int subArr[lengthSub];

    wait(NULL);

    if (read(STDIN_FILENO, subArr, sizeof(int) * lengthSub) < 0)
    {
        exit(EXIT_FAILURE);
    }

    checkMessageFromParent(massege, subArr, lengthSub, &maxAndAvg);

    if (write(STDOUT_FILENO, &maxAndAvg, sizeof(MaxAndAvg)) < 0)
    {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
