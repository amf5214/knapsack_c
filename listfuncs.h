// imports
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Function to split string by a delimiator
@param pathStr:char* string that needs to be split
@param delimiator:char character that represents the delimiator used
@param num:int* pointer to integer number representing the number of values
@return returns an array of int values
*/
int* splitPath(char* pathStr, char delimiator, int* num);

/*
Function to convert an array of integers to a string
@param values:int* value array to convert to stirng
@param delimiator:char* delimiator to be inserted into the string
@param size:int size of the array
@return string representing concatenated string of array values with delimiator
*/
char* convertArrayToString(int* values, char* delimiator, int size);
