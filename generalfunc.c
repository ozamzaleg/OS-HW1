#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "generalfunc.h"

int *readArrFromFile(char *fileName, char *letter, int *len)
{
	int *arr;
	FILE *file = fopen(fileName, "r");
	if (!file)
	{
		printf("%s", "cant open the file");
	}

	if (fscanf(file, "%c%d", letter, len) != 2)
	{
		ferror(file);
		return NULL;
	}

	arr = (int *)malloc(sizeof(int) * (*len));
	if (!arr)
	{
		printf("%s", "allocate not succss");
		return NULL;
	}
	for (int i = 0; i < (*len); i++)
	{
		if (fscanf(file, "%d", &arr[i]) != 1)
		{
			ferror(file);
			return NULL;
		}
	}
	return arr;
}

int *readArrFromUser(char *letter, int *len)
{
	int *arr;
	printf("%s", "please enter letter:\n");
	scanf("%c", letter);
	printf("%s", "please enter the how many numbers:\n");
	scanf("%d", len);
	arr = (int *)malloc(sizeof(int) * (*len));
	if (!arr)
	{
		printf("%s", "allocate not succss");
		return NULL;
	}
	printf("%s", "");

	for (int i = 0; i < (*len); i++)
	{
		scanf("%d", &arr[i]);
	}
	return arr;
}
