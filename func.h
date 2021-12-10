#include "definition.h"

#ifndef FUNC_H_
#define FUNC_H_

void finalRisult(char *argv[], int argc, MaxAndAvg first, MaxAndAvg second, int lenForChild1, int lenForChild2, int lenth);
float getAvgParent(float fromChild1, float fromChild2, int lenForChild1, int lenForChild2, int lenth);
int getMaxParent(int fromChild1, int fromChild2);
int ifExisAvgMax(char *argv[], int argc, int *subArr, int lengthSub, MaxAndAvg *maxAndAvg);
int *createSubArr(int *arr, int lenNewSub);
float getAvg(int *arr, int length);
int getMax(int *arr, int length);
int ifContainFunction(char *argv[], int argc);
char *getNameFile(char *argv[], int argc);

#endif /* FUNC_H_ */
