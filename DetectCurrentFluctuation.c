#include "DetectCurrentFluctuation.h"

/* Comparator Function for qsort */
int compareGivenInputs (const void * firstInput, const void * secondInput) {
    return ( *(int*)firstInput - *(int*)secondInput );
}

int* provideSortedArray(int *currentReadings, int NumberOfSamples) {
    qsort(currentReadings,NumberOfSamples,sizeof(int),compareGivenInputs);
    return currentReadings;
}

/* Returns an array with Count of Elements provided in input array*/
int* provideCountOfDistinctElementsInArray(int *ArrayElements, int sizeOfArray) {
    int *arrayToStoreCount;
    arrayToStoreCount = (int*)calloc(MAX_NUMBER_OF_READINGS, sizeof(int));
    
    for(int i=0; i<sizeOfArray; i++)
    {
        int index = ArrayElements[i];
        arrayToStoreCount[index]++;
    }
    return arrayToStoreCount;
}

/* Finds the Count of range and returns the number of distinct ranges */
int findAndProvideRangeCount(int* countOfReadings) {
    int minRange = -1, maxRange = -1, rangeCounter = 0, readingsCounter = 0;
  
    for(int i=0; i<MAX_NUMBER_OF_READINGS; i++)
    {
        if((countOfReadings[i] != 0))
        {
            readingsCounter += countOfReadings[i];
            if(minRange == -1)
            {
                minRange = i;
                maxRange = i;
            }
            else
            {
                maxRange = i;
            }
        }
        else if(readingsCounter != 0)
        {
            minValues[rangeCounter] = minRange;
            maxValues[rangeCounter] = maxRange;
            countValues[rangeCounter] = readingsCounter;
            rangeCounter++;
            readingsCounter = 0;
            minRange = -1;
            maxRange = -1;
        }  
    }
    return rangeCounter;
}

void formatAndPrintToConsole(int NoOfRanges) {
    for(int i=0; i<NoOfRanges; i++)
    {
        printf("%d-%d, %d\n",minValues[i],maxValues[i],countValues[i]);
    }
}

/* CoOrdinator function that uses other helper functions to do the job */
int Capture_and_Print_Current_values(int *currentReadings, int NumberOfSamples)
{
    int *sortedInputArray = provideSortedArray(currentReadings,NumberOfSamples);
    int *countOfReadings = provideCountOfDistinctElementsInArray(sortedInputArray,NumberOfSamples);
    int NoOfRanges = findAndProvideRangeCount(countOfReadings);
    (void)formatAndPrintToConsole(NoOfRanges);
    return NoOfRanges;
}
