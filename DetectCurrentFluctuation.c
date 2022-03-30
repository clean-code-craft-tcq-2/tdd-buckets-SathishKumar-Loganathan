#include "DetectCurrentFluctuation.h"

int minValues[MAX_NUMBER_OF_READINGS] = {0};
int maxValues[MAX_NUMBER_OF_READINGS] = {0};
int countValues[MAX_NUMBER_OF_READINGS] = {0};
int *digitalArray,*arrayToStoreCount;

/* Comparator Function for qsort */
int compareGivenInputs (const void * firstInput, const void * secondInput) {
    return ( *(int*)firstInput - *(int*)secondInput );
}

int* provideSortedArray(int *currentReadings, int NumberOfSamples) {
    qsort(currentReadings,NumberOfSamples,sizeof(int),compareGivenInputs);
    return currentReadings;
}

/* Returns Digital value (Range: 0A to 10A) for the input 12bit analog value */
int PerformADC_12bit_max10Amps(int analogValue) {
    return (analogValue * 10)/4094;
}

/* Returns an array with Count of Elements provided in input array*/
int* provideCountOfDistinctElementsInArray(int *ArrayElements, int sizeOfArray) {
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

int* analogToDigitalConverter(int *analogArray, int sizeOfAnalogArray) {
    int loopCounter;
    digitalArray = (int*)calloc(sizeOfAnalogArray, sizeof(int));
    for(loopCounter=0; loopCounter < sizeOfAnalogArray; loopCounter++)
    {
        if(analogArray[loopCounter] != 4095) //Hey its an Error.. Let's ignore  it!!
            digitalArray[loopCounter] = round(PerformADC_12bit_max10Amps(analogArray[loopCounter]));
    }
    return digitalArray;
}

bool isInputValid(int *inputAnalogReadings, int NumberOfSamples) {
    if((inputAnalogReadings == NULL) || (NumberOfSamples <= 0))
        return 0;
    else if((inputAnalogReadings[0] >= 4095) && (NumberOfSamples == 1))
        return 0;
    else
        return 1;
}

/* CoOrdinator function that uses other helper functions to do the job */
int Capture_and_Print_Current_values(int *inputAnalogReadings, int NumberOfSamples) {
    if(isInputValid(inputAnalogReadings,NumberOfSamples)) {
        int *digitalConvertedArray = analogToDigitalConverter(inputAnalogReadings,NumberOfSamples);
        int *sortedInputArray = provideSortedArray(digitalConvertedArray,NumberOfSamples);
        int *countOfReadings = provideCountOfDistinctElementsInArray(sortedInputArray,NumberOfSamples);
        int NoOfRanges = findAndProvideRangeCount(countOfReadings);
        (void)formatAndPrintToConsole(NoOfRanges);
        free(digitalArray);
        free(arrayToStoreCount);
        return NoOfRanges;
    }
    return 0;
}
