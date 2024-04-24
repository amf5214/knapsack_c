// imports 
#include "fileoperations.h"

// constants
int MAX_NAME_LENGTH = 255;
int MAX_WEIGHT = 50;

/*
Function to count the number of lines in a file
@param file:FILE* file that we are counting the length of
@return number of lines in a file as an int
*/
int countLines(FILE* file) {
    int lines = 0;
    char line[MAX_NAME_LENGTH];
    while (fgets(line, sizeof(line), file))
        lines++;
    rewind(file);
    return lines;
}

/*
Function to parse items from a csv file
@param file:FILE* file object
@param labels:char** array of strings representing item lables
@param val:int* integer array representing the value of each item
@param wt:int* integer array representing the weight of each item
*/
void parseItems(FILE *file, char** labels, int *val, int *wt)
{
    char line[MAX_NAME_LENGTH];
    char *token = (char*) malloc(sizeof(char) * MAX_NAME_LENGTH);
    int index = 0;
    while (fgets(line, sizeof(line), file))
    {
        token = strtok(line, ",");
        strcpy(labels[index], token);
        token = strtok(NULL, ",");
        val[index] = atoi(token);
        token = strtok(NULL, ",");
        wt[index] = atoi(token);
        index++;
    }
}

