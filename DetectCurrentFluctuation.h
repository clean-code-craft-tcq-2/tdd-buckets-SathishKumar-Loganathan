#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */

#define MAX_NUMBER_OF_READINGS 50

int minValues[MAX_NUMBER_OF_READINGS];
int maxValues[MAX_NUMBER_OF_READINGS];
int countValues[MAX_NUMBER_OF_READINGS];

extern int Capture_and_Print_Current_values(int *currentReadings, int NumberOfSamples);
