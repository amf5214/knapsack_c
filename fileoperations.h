// imports 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Function to count the number of lines in a file
@param file:FILE* file that we are counting the length of
@return number of lines in a file as an int
*/
int countLines(FILE* file);

/*
Function to parse items from a csv file
@param file:FILE* file object
@param labels:char** array of strings representing item lables
@param val:int* integer array representing the value of each item
@param wt:int* integer array representing the weight of each item
*/
void parseItems(FILE *file, char** labels, int *val, int *wt);
