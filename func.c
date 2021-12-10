#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "func.h"
#include "definition.h"

void finalRisult(char *argv[], int argc, MaxAndAvg first, MaxAndAvg second, int lenForChild1, int lenForChild2, int lenth)
{

	if (ifContainFunction(argv, argc) == 3)
	{
		float avg = getAvgParent(first.avg, second.avg, lenForChild1, lenForChild2, lenth);
		int max = getMaxParent(first.max, second.max);
		printf("The avg is: %.3f\n", avg);
		printf("The max is: %d", max);
	}
	else if (ifContainFunction(argv, argc) == 1)
	{
		float avg = getAvgParent(first.avg, second.avg, lenForChild1, lenForChild2, lenth);
		printf("The avg is: %.3f", avg);
	}
	else if (ifContainFunction(argv, argc) == 2)
	{
		int max = getMaxParent(first.max, second.max);
		printf("The max is: %d", max);
	}
	else
	{
		printf("%s", "You did not choose avg or max");
	}
}

float getAvgParent(float fromChild1, float fromChild2, int lenForChild1, int lenForChild2, int lenth)
{
	float sum = fromChild1 * lenForChild1 + fromChild2 * lenForChild2;
	return sum / lenth;
}

int getMaxParent(int fromChild1, int fromChild2)
{
	if (fromChild1 > fromChild2)
	{
		return fromChild1;
	}

	return fromChild2;
}

int ifExisAvgMax(char *argv[], int argc, int *subArr, int lengthSub,
				 MaxAndAvg *maxAndAvg)
{

	if (ifContainFunction(argv, argc) == 3)
	{
		maxAndAvg->avg = getAvg(subArr, lengthSub);
		maxAndAvg->max = getMax(subArr, lengthSub);
		return 0;
	}
	if (ifContainFunction(argv, argc) == 2)
	{
		maxAndAvg->max = getMax(subArr, lengthSub);
		return 0;
	}
	if (ifContainFunction(argv, argc) == 1)
	{
		maxAndAvg->avg = getAvg(subArr, lengthSub);
		return 0;
	}

	return -1;
}

//max and avg 3,max 2,avg 1,no -1
int ifContainFunction(char *argv[], int argc)
{
	int flegContainAvg = 0;
	int flegContainMax = 0;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], MAX) == 0)
		{
			flegContainMax = 1;
		}
		if (strcmp(argv[i], AVG) == 0)
		{
			flegContainAvg = 1;
		}
	}
	if (flegContainMax && flegContainAvg)
	{
		return 3;
	}
	else if (flegContainMax)
	{
		return 2;
	}
	else if (flegContainAvg)
	{
		return 1;
	}

	return -1;
}
char *getNameFile(char *argv[], int argc)
{
	for (int i = 0; i < argc; i++)
	{
		if (strstr(argv[i], TEXT) != NULL)
		{
			return argv[i];
		}
	}
	return NULL;
}

int *createSubArr(int *arr, int lenNewSub)
{
	int *subArr = (int *)malloc(sizeof(int) * lenNewSub);

	if (!subArr)
	{
		return subArr;
	}

	memcpy(subArr, arr, sizeof(int) * lenNewSub);

	return subArr;
}

float getAvg(int *arr, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum = sum + arr[i];
	}
	return (float)sum / length;
}

int getMax(int *arr, int length)
{
	int max = arr[0];
	for (int i = 1; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
