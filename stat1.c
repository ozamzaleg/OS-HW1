#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "func.h"
#include "generalfunc.h"
#include "communication.h"
#include "definition.h"

int main(int argc, char *argv[])
{

	int *arr;
	char letter = ' ';
	int lenth = 0;
	int lenForChild[PROCESS_NUM];
	int pids[PROCESS_NUM];
	int pipes[PROCESS_NUM][2];

	//if no max and no
	if ((ifContainFunction(argv, argc)) == -1)
	{
		fprintf(stderr, "Error, No function enter\n");
		exit(EXIT_FAILURE);
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

	lenForChild[0] = lenth / 2;
	lenForChild[1] = lenth - (lenth / 2);

	///////////////////childrens//////////////////////

	for (int i = 0; i < PROCESS_NUM; i++)
	{
		if (pipe(pipes[i]) < 0)
		{
			fprintf(stderr, "creating pipe failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < PROCESS_NUM; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			fprintf(stderr, "creating fork failed\n");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{

			for (int j = 0; j < PROCESS_NUM; j++)
			{
				if (i != j)
				{
					close(pipes[j][0]);
					close(pipes[j][1]);
				}
				else
				{
					responseFromChild(pipes[i], lenForChild[i], argv, argc);
				}
			}

			exit(EXIT_SUCCESS);
		}
	}

	///////////////////parents///////////////////////

	MaxAndAvg strctFromChild1;
	MaxAndAvg strctFromChild2;

	int *subArr1 = createSubArr(arr, lenForChild[0]);
	int *subArr2 = createSubArr(arr + lenForChild[0], lenForChild[1]);

	if (write(pipes[0][1], subArr1, sizeof(int) * lenForChild[0]) < 0)
	{
		exit(EXIT_FAILURE);
	}

	if (write(pipes[1][1], subArr2, sizeof(int) * lenForChild[1]) < 0)
	{
		exit(EXIT_FAILURE);
	}

	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);

	close(pipes[0][1]);
	close(pipes[1][1]);

	// read arr from childs////

	if (read(pipes[0][0], &strctFromChild1, sizeof(MaxAndAvg)) < 0)
	{
		exit(EXIT_FAILURE);
	}

	if (read(pipes[1][0], &strctFromChild2, sizeof(MaxAndAvg)) < 0)
	{
		exit(EXIT_FAILURE);
	}

	close(pipes[0][0]);
	close(pipes[1][0]);

	finalRisult(argv, argc, strctFromChild1, strctFromChild2, lenForChild[0], lenForChild[1], lenth);

	free(arr);
	free(subArr1);
	free(subArr2);

	return 0;
}