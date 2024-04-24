// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Type definitions
typedef struct Node{
    char* name;
    struct Node* child;
    struct Node* parent;
} Node;

typedef struct Queue {
    struct Node* head;
    struct Node* tail;
} Queue;

/*
Function to enqueue a new node onto the queue provided
@param queue:Queue* pointer to queue being modified
@param newNode:Node* pointer to node being enqueued
*/
void enqueue(Queue* queue, Node* newNode);

/*
Function to dequeue the head node from the queue provided
@param queue:Queue* pointer to queue being modified
@return pointer to node that was dequeued 
*/
Node* dequeue(Queue* queue);

/*
Function to print queue onto the console
@param queue:Queue* pointer to queue being printed out
*/
void printQueue(Queue* queue);

