#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#include "generalfunc.h"
#include "func.h"
#include "definition.h"

int main(int argc, char *argv[])
{
	int *arr;
	char latter;
	int lenForChild[PROCESS_NUM];
	char dir[MAX_DIR_LEN];
	char lenForChildString[2][MAX_STRING_LEN];
	int pids[PROCESS_NUM];
	int pipes[PROCESS_NUM][2];
	int *subArr[PROCESS_NUM];
	int lenth;
	MaxAndAvg maxAndAvg1;
	MaxAndAvg maxAndAvg2;

	getcwd(dir, MAX_DIR_LEN);
	strcat(dir, "/child2");

	//if no max and no
	if ((ifContainFunction(argv, argc)) == -1)
	{
		printf("%s", "Error, No function enter");
		exit(EXIT_FAILURE);
	}

	char *name = getNameFile(argv, argc);

	if (name != NULL)
	{

		arr = readArrFromFile(name, &latter, &lenth);
	}
	else
	{
		arr = readArrFromUser(&latter, &lenth);
	}

	lenForChild[1] = lenth - (lenth / 2);
	lenForChild[0] = lenth / 2;

	subArr[0] = createSubArr(arr, lenForChild[0]);
	subArr[1] = createSubArr(arr + lenForChild[0], lenForChild[1]);

	sprintf(lenForChildString[0], "%d", lenForChild[0]);
	sprintf(lenForChildString[1], "%d", lenForChild[1]);

	//max and avg 3,max 2,avg 1,no -1
	char *parmList[] = {"child2", NULL, NULL, NULL};
	char *stringFunc[] = {NULL};
	char *lenSubArr[] = {NULL};

	int inputFunction = ifContainFunction(argv, argc);

	switch (inputFunction)
	{
	case 3:
		stringFunc[0] = MAX_AVG;
		break;
	case 2:
		stringFunc[0] = MAX;
		break;
	case 1:
		stringFunc[0] = AVG;
		break;
	}

	parmList[2] = stringFunc[0];

	///////////////////////childs////////////////////////////////

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
					dup2(pipes[j][1], STDOUT_FILENO);
					dup2(pipes[j][0], STDIN_FILENO);
					close(pipes[j][0]);
					close(pipes[j][1]);

					if (write(STDOUT_FILENO, subArr[j], sizeof(int) * lenForChild[j]) < 0)
					{
						exit(EXIT_FAILURE);
					}
					lenSubArr[0] = lenForChildString[j];
					parmList[1] = lenSubArr[0];
					execv(dir, parmList);
					fprintf(stderr, "function execv failed\n");
					exit(EXIT_FAILURE);
				}
			}
			exit(EXIT_SUCCESS);
		}
	}

	////////////////////////perent////////////////////////////

	waitpid(pids[0], NULL, 0);

	if (read(pipes[0][0], &maxAndAvg1, sizeof(MaxAndAvg)) < 0)
	{
		exit(EXIT_FAILURE);
	}

	waitpid(pids[1], NULL, 0);

	if (read(pipes[1][0], &maxAndAvg2, sizeof(MaxAndAvg)) < 0)
	{
		exit(EXIT_FAILURE);
	}

	finalRisult(argv, argc, maxAndAvg1, maxAndAvg2, lenForChild[0], lenForChild[1], lenth);

	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);

	free(arr);
	for (int i = 0; i < PROCESS_NUM; i++)
	{
		free(subArr[i]);
	}

	return 0;
}
