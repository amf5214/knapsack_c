// imports
#include "listfuncs.h"


/*
Function to split string by a delimiator
@param pathStr:char* string that needs to be split
@param delimiator:char character that represents the delimiator used
@param num:int* pointer to integer number representing the number of values
@return returns an array of int values
*/
int* splitPath(char* stringS, char delimiter, int* num) {
    int length = strlen(stringS);
    char* pathStr = (char*) malloc(sizeof(char) * length + 1);
    strcpy(pathStr, stringS);

    int countDel = 0;

    // Count the number of delimiters
    for (int i = 0; i < length; i++) {
        if (pathStr[i] == delimiter) {
            countDel++;
        }
    }

    // Allocate memory for values
    int* values = (int*) malloc(sizeof(int) * (countDel + 1));
    if (!values) {
        // Handle memory allocation failure
        return NULL;
    }

    char* token = strtok(pathStr, &delimiter);
    while (token) {
        int intValue = atoi(token);
        values[*num] = intValue;
        (*num)++;
        token = strtok(NULL, &delimiter);
    }

    return values;
}

/*
Function to convert an array of integers to a string
@param values:int* value array to convert to stirng
@param delimiator:char* delimiator to be inserted into the string
@param size:int size of the array
@return string representing concatenated string of array values with delimiator
*/
char* convertArrayToString(int* values, char* delimiter, int size) {
    // Calculate the total length needed for the concatenated string
    int totalLength = 0;
    for (int i = 0; i < size; i++) {
        totalLength += snprintf(NULL, 0, "%d", values[i]); // Get the length of each value
        if (i > 0) {
            totalLength += strlen(delimiter); // Add delimiter length
        }
    }
    totalLength++; // Account for the null terminator

    // Allocate memory for the return string
    char* returnString = (char*) malloc(totalLength);
    if (!returnString) {
        // Handle memory allocation failure
        return NULL;
   }

    // Initialize the return string with the first value
    snprintf(returnString, totalLength, "%d", values[0]);

    // Append subsequent values with the delimiter
    for (int i = 1; i < size; i++) {
	    strcat(returnString, delimiter);
    	    snprintf(returnString + strlen(returnString), totalLength - strlen(returnString), "%d", values[i]);
    }

    return returnString;
}

int listFunctionsMain() {

    char* testStr = "1-3-5-7-9";
    int testArr[4] = {1,2,3,4};
    char delim = '-';

    int* count = (int*) malloc(sizeof(int));
    int* values = splitPath(testStr, delim, count);

    printf("%d\n", *count);
    for(int i = 0; i < *count; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    char* output = convertArrayToString(testArr, "-", 3);

    printf("%s\n", output);

    free(count);
    free(output);
    free(values);

    return 0;
}

