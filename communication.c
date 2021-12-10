#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "func.h"
#include "definition.h"
#include "communication.h"

void responseFromChild(int *fd, int lenthArrChild, char *argv[], int argc)
{
	MaxAndAvg child;
	int arrChild[lenthArrChild];

	if (read(fd[0], arrChild, sizeof(int) * lenthArrChild) < 0)
	{
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	if ((ifExisAvgMax(argv, argc, arrChild, lenthArrChild, &child)) == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (write(fd[1], &child, sizeof(MaxAndAvg)) < 0)
	{
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
}

void checkMessageFromParent(char *message, int *subArr, int lengthSub, MaxAndAvg *maxAndAvg)
{

	if (strcmp(message, MAX_AVG) == 0)
	{
		maxAndAvg->avg = getAvg(subArr, lengthSub);
		maxAndAvg->max = getMax(subArr, lengthSub);
	}
	else if (strcmp(message, MAX) == 0)
	{
		maxAndAvg->max = getMax(subArr, lengthSub);
	}
	else if (strcmp(message, AVG) == 0)
	{
		maxAndAvg->avg = getAvg(subArr, lengthSub);
	}
}