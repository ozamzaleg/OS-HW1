#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "func.h"
#include "generalfunc.h"
#include "communication.h"

int main(int argc, char *argv[])
{

	int *arr;
	char letter = ' ';
	int lenth = 0;
	int lenForChild1;
	int lenForChild2;
	int fd1[2];
	int fd2[2];

	//if no max and no
	if ((ifContainFunction(argv, argc)) == -1)
	{
		printf("%s", "Error, No function enter");
		return 0;
	}

	char *name = getNameFile(argv, argc);

	if (name != NULL)
	{
		arr = readArrFromFile(name, &letter, &lenth);
	}
	else
	{
		arr = readArrFromUser(&letter, &lenth);
	}

	///////////////////children//////////////////////

	lenForChild1 = lenth / 2;
	lenForChild2 = lenth - (lenth / 2);

	pipe(fd1);
	pipe(fd2);

	int pid1 = fork();
	if (pid1 < 0)
	{
		return 2;
	}
	if (pid1 == 0)
	{
		close(fd2[0]);
		close(fd2[1]);
		if ((responseFromChild(fd1, lenForChild1, argv, argc) == -1))
		{
			return 0;
		}
	}

	int pid2 = fork();
	if (pid2 < 0)
	{
		return 5;
	}

	if (pid2 == 0)
	{
		close(fd1[0]);
		close(fd1[1]);
		if ((responseFromChild(fd2, lenForChild2, argv, argc) == -1))
		{
			return 0;
		}
	}

	///////////////////parents///////////////////////

	MaxAndAvg strctFromChild1;
	MaxAndAvg strctFromChild2;

	int *subArr1 = createSubArr(arr, lenForChild1);
	int *subArr2 = createSubArr(arr + lenForChild1, lenForChild2);

	if (write(fd1[1], subArr1, sizeof(int) * lenForChild1) < 0)
	{
		return 0;
	}

	if (write(fd2[1], subArr2, sizeof(int) * lenForChild2) < 0)
	{
		return 0;
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	close(fd1[1]);
	close(fd2[1]);

	// read arr from childs////

	if (read(fd1[0], &strctFromChild1, sizeof(MaxAndAvg)) < 0)
	{
		return 9;
	}

	if (read(fd2[0], &strctFromChild2, sizeof(MaxAndAvg)) < 0)
	{
		return 9;
	}

	close(fd1[0]);
	close(fd2[0]);

	finalRisult(argv, argc, strctFromChild1, strctFromChild2);

	return 0;
}