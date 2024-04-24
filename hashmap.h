// Imports 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Structure to hold a specified path
typedef struct Path {
    char* name;
    int value;
    int weight;
    struct Path* next;
} Path;


// Structure to hold the entire hashmap
typedef struct Hashmap {
    Path** paths;
    int size;
} Hashmap;

/* 
Function to instantiate a hashmap and allocate memory
@param map:Hashmap** pointer to Hashmap pointer
@param size:int represents the size of the hashmap
*/
void instantiateHashmap(Hashmap** map, int size);

/*
Function to hash a string and return a hashed int index
@param name:char* string that neeeds to be hashed 
@return returns the hashed int value
*/
unsigned int hash(char* name);

/*
Function to insert a path into a Hashmap of paths
@param map:Hashmap* Hashmap object that is being modified
@param key:char* key of the object being inserted
@param value:int value of the path
@param weight:int weight of the objects included in the path
*/
void insert(Hashmap* map, char* key, int value, int weight);

/*
Function to find a specified key in the provided hashmap
@param map:Hashmap* hashmap that is being searched in 
@param key:char* key value that is being searched for
@return returns a pointer to the Path object that was found 
if no object was found, then NULL will be returned
*/
Path* find(Hashmap* map, char* key);

/*
Function to print out a Hashmap to the console
@param map:Hashmap* Hashmap that is being printed
*/
void printHashmap(Hashmap* map);

/*
Function to instantiate path object
@param label:char* item label
@param value:int value of the item
@param weight:int weight of the item
@return returns a pointer to the Path object
*/
Path* createPath(char* label, int value, int weight);

/*
Function to free hashmap using free list function declared
@param map:Hashmap hashmap being free'd
*/
void freeHashmap(Hashmap* map);

/*
Helper function to free a linked list within the hashmap
@param head:Path* list head 
*/
void freeList(Path* head);

