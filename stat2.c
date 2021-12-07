#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "generalfunc.h"
#include "func.h"

/* Version A: passing child args through execve */
int main(int argc, char *argv[])
{
	pid_t pid1;
	pid_t pid2;
	int *arr;
	char latter;
	int lenForChild1;
	int lenForChild2;
	char dir[100];

	char lenForChild1String[20];
	char lenForChild2String[20];
	int fd1[2];
	int fd2[2];
	int lenth;
	MaxAndAvg maxAndAvg1;
	MaxAndAvg maxAndAvg2;

	getcwd(dir, 100);
	strcat(dir, "/child2");

	//if no max and no
	if ((ifContainFunction(argv, argc)) == -1)
	{
		printf("%s", "Error, No function enter");
		return 0;
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

	lenForChild2 = lenth - (lenth / 2);
	lenForChild1 = lenth / 2;

	int *subArr1 = createSubArr(arr, lenForChild1);
	int *subArr2 = createSubArr(arr + lenForChild1, lenForChild2);

	sprintf(lenForChild1String, "%d", lenForChild1);
	sprintf(lenForChild2String, "%d", lenForChild2);

	//max and avg 3,max 2,avg 1,no -1
	char *parmList[] = {"child2", NULL, NULL, NULL};
	char *stringFunc[] = {NULL};
	char *lenSubArr[] = {NULL};

	//chack what function in the stdin
	int inputFunction = ifContainFunction(argv, argc);

	switch (inputFunction)
	{
	case 3:
		stringFunc[0] = "MAX-AVG";
		break;
	case 2:
		stringFunc[0] = "MAX";
		break;
	case 1:
		stringFunc[0] = "AVG";
		break;
	}

	parmList[2] = stringFunc[0];

	///////////////////////child1////////////////////////////////

	lenSubArr[0] = lenForChild1String;
	parmList[1] = lenSubArr[0];

	if (pipe(fd1) == -1)
	{
		printf("in\n");

		return 1;
	}
	pid1 = fork();

	if (pid1 == -1)
		printf("fork error");
	else if (pid1 == 0)
	{

		dup2(fd1[1], STDOUT_FILENO);
		dup2(fd1[0], STDIN_FILENO);

		close(fd1[0]);
		close(fd1[1]);

		if (write(STDOUT_FILENO, subArr1, sizeof(int) * lenForChild1) < 0)
		{
			return 9;
		}

		execv(dir, parmList);
		printf("Return not expected. Must be an execv error.n");
	}

	//////////////////////////child2/////////////////////////////

	lenSubArr[0] = lenForChild2String;
	parmList[1] = lenSubArr[0];

	if (pipe(fd2) == -1)
	{
		printf("in\n");

		return 1;
	}
	pid2 = fork();

	if (pid2 == -1)
		printf("fork error");
	else if (pid2 == 0)
	{

		dup2(fd2[1], STDOUT_FILENO);
		dup2(fd2[0], STDIN_FILENO);

		close(fd2[0]);
		close(fd2[1]);

		if (write(STDOUT_FILENO, subArr2, sizeof(int) * lenForChild2) < 0)
		{
			return 9;
		}

		execv(dir, parmList);
		printf("Return not expected. Must be an execv error.n");
	}

	////////////////////////perent////////////////////////////

	waitpid(pid1, NULL, 0);

	if (read(fd1[0], &maxAndAvg1, sizeof(MaxAndAvg)) < 0)
	{
		return 9;
	}

	waitpid(pid2, NULL, 0);

	if (read(fd2[0], &maxAndAvg2, sizeof(MaxAndAvg)) < 0)
	{
		return 9;
	}

	finalRisult(argv, argc, maxAndAvg1, maxAndAvg2);

	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);

	return 0;
}
