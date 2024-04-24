// imports 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fileoperations.h"
#include "statmath.h"
#include "hashmap.h"
#include "queuemodel.h"
#include "listfuncs.h"
#include <limits.h>

// constants
int MAX_LABEL_LENGTH = 255;
int MAX_SOLUTION_WEIGHT = 50;
float WV_ZSCORE_THRESHOLD = -0.5;

/*
Function to print an item set to the console
@param labels:char** list of strings representing the item labels
@param weights:int* array of integers representing the weight of each item
@param values:int* array of integers representing the value of each item
@param size:int size of the item set
*/
void printListSet(char** labels, int* weights, int* values, unsigned long size);

/*
Function to instantiate an itemset
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
void instantiateItemset(char*** labels, int** values, int** weights, unsigned long size);

/*
Function to free an itemset
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
void freeItemset(char*** labels, int** values, int** weights, unsigned long size);

/*
Function to weight each item's value by the ratio of their weight to the max weight.
@param weightedValuesArray:float* pointer to array for weighted values to be stored
@param weights:int* array of integers representing item weights
@param values:int* array of integers representing item values
@param size:int integer representing the size of the item set
*/
void calculateWeightedValues(float* weightedValuesArray, int* weights, int* values, unsigned long size);

/*
Function that will create a z-score for each item based on the weight value and filter
out items below the threshold
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
unsigned long filterItemsByWeightedValue(char*** labels, int** values, int** weights, unsigned long size);
