#ifndef FUNC_H_
#define FUNC_H_

#define MAX "-max"
#define AVG "-avg"
#define TEXT ".txt"

typedef struct
{

	int max;
	float avg;

} MaxAndAvg;

void finalRisult(char *argv[], int argc, MaxAndAvg first, MaxAndAvg second);
float getAvgParent(float fromChild1, float fromChild2);
int getMaxParent(int fromChild1, int fromChild2);
int ifExisAvgMax(char *argv[], int argc, int *subArr, int lengthSub, MaxAndAvg *maxAndAvg);
int *createSubArr(int *arr, int lenNewSub);
float getAvg(int *arr, int length);
int getMax(int *arr, int length);
int ifContainFunction(char *argv[], int argc);
char *getNameFile(char *argv[], int argc);

#endif /* FUNC_H_ */
