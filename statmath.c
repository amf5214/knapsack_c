// imports
#include "statmath.h"

/*
Function to calculate the mean of data from an array
@param values:int* array of values to take the mean of
@param num:int number of items in the provided array
@return value of the mean of the data
*/
float computeMean(float* values, int num) {
    float sum = 0;
    for(int i = 0; i < num; i++) {
        sum += values[i];
    }

    return (sum / num);
}

/*
Function to calculate the standard deviation of data from an array
@param values:int* array of values to take the standard deviation of
@param num:int number of items in the provided array
@param mean:float mean of the provided data
@return value of the standard deviation of the data
*/
float computeStd(float* values, int num, float mean) {
    float std = 0.0;
    for(int i = 0; i < num; i++) {
        std += pow(values[i] - mean, 2);
    }

    return sqrt(std / num);
}

/*
Function to calculate the z-scores of data from an array
@param values:int* array of values to calculate the z-scores of
@param num:int number of items in the provided array
@return array of z-scores
*/
float* calculateZScores(float* values, int num) {

    float* zScores = (float*) malloc(sizeof(float) * num);

    float mean = computeMean(values, num);
    float std = computeStd(values, num, mean);

    for(int i = 0; i < num; i++) {
        zScores[i] = (values[i] - mean) / std;
    }

    return zScores;

}

int statMain() {
    int count = 7;
    float values[7] = {10.0, 5.0, 6.0, 4.0, 23.0, 42.0, 12.0};

    float* zScores = calculateZScores(values, count);

    for(int i = 0; i < count; i++) {
        printf("%f\n", zScores[i]);
    }

    free(zScores);

    return 0;
}
