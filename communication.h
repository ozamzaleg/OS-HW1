#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "definition.h"

void responseFromChild(int *fd, int lenthArrChild, char *argv[], int argc);
void checkMessageFromParent(char *message, int *subArr, int lengthSub, MaxAndAvg *maxAndAvg);
#endif /* COMMUNICATION_H_ */