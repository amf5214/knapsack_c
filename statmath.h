// imports
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
Function to calculate the mean of data from an array
@param values:int* array of values to take the mean of
@param num:int number of items in the provided array
@return value of the mean of the data
*/
float computeMean(float* values, int num);

/*
Function to calculate the standard deviation of data from an array
@param values:int* array of values to take the standard deviation of
@param num:int number of items in the provided array
@param mean:float mean of the provided data
@return value of the standard deviation of the data
*/
float computeStd(float* values, int num, float mean);

/*
Function to calculate the z-scores of data from an array
@param values:int* array of values to calculate the z-scores of
@param num:int number of items in the provided array
@return array of z-scores
*/
float* calculateZScores(float* values, int num);


