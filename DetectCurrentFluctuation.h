#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
#include <math.h>       /* round */
#include <stdbool.h>    /* boolean support */

#define MAX_NUMBER_OF_READINGS 50

extern int Capture_and_Print_Current_values(int *currentReadings, int NumberOfSamples);
