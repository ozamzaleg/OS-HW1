#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"

int responseFromChild(int *fd, int lenthArrChild, char *argv[], int argc)
{
	MaxAndAvg child;
	int arrChild[lenthArrChild];

	if (read(fd[0], arrChild, sizeof(int) * lenthArrChild) < 0)
	{
		return 0;
	}
	close(fd[0]);
	if ((ifExisAvgMax(argv, argc, arrChild, lenthArrChild, &child)) == -1)
	{
		return -1;
	}
	if (write(fd[1], &child, sizeof(MaxAndAvg)) < 0)
	{
		return 0;
	}
	close(fd[1]);
	return 0;
}
