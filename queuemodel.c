// imports 
#include "queuemodel.h"

/*
Function to enqueue a new node onto the queue provided
@param queue:Queue* pointer to queue being modified
@param newNode:Node* pointer to node being enqueued
*/
void enqueue(Queue* queue, Node* newNode) {
    if (queue->head == NULL & queue->tail == NULL) {
	printf("Queue initial setup\n");
        queue->head = newNode;
        queue->tail = newNode;
    } else {
	printf("Aux queue injection ocurring...\n");
        queue->tail->parent = newNode;
        newNode->child = queue->tail;
        queue->tail = newNode;
    }
}

/*
Function to dequeue the head node from the queue provided
@param queue:Queue* pointer to queue being modified
@return pointer to node that was dequeued 
*/
Node* dequeue(Queue* queue) {
    if (queue->head == NULL) {
        return NULL;
    } else {
        Node* head = queue->head;
        queue->head = head->parent;
        if (queue->head != NULL) {
            queue->head->child = NULL;
        } else {
            queue->tail = NULL;
        }
        head->parent = NULL;
        head->child = NULL;
        return head;
    }
}


/*
Function to print queue onto the console
@param queue:Queue* pointer to queue being printed out
*/
void printQueue(Queue* queue) {
    if(queue->head != NULL) {
        Node* current = (Node*) malloc(sizeof(Node));
        current = queue->head;
        while(current != NULL) {
            printf("Node = %s\n", current->name);
            if(current->parent != NULL) {
                current = current->parent;
            } else {
                current = NULL;
            }
        }
    }
}
 
int queueMain() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    Node* node1 = (Node*) malloc(sizeof(Node));
    node1->name = (char*) malloc(sizeof(char*));
    node1->name = "Node 1";
    Node* node2 = (Node*) malloc(sizeof(Node));
    node2->name = (char*) malloc(sizeof(char*));
    node2->name = "Node 2";
    Node* node3 = (Node*) malloc(sizeof(Node));
    node3->name = (char*) malloc(sizeof(char*));
    node3->name = "Node 3";
    Node* node4 = (Node*) malloc(sizeof(Node));
    node4->name = (char*) malloc(sizeof(char*));
    node4->name = "Node 4";
    Node* node5 = (Node*) malloc(sizeof(Node));
    node5->name = (char*) malloc(sizeof(char*));
    node5->name = "Node 5";

    Node* testNode1 = (Node*) malloc(sizeof(Node));
    testNode1->name = (char*) malloc(sizeof(char*));
    
    Node* testNode2 = (Node*) malloc(sizeof(Node));
    testNode2->name = (char*) malloc(sizeof(char*));

    Node* testNode3 = (Node*) malloc(sizeof(Node));
    testNode3->name = (char*) malloc(sizeof(char*));

    Node* testNode4 = (Node*) malloc(sizeof(Node));
    testNode4->name = (char*) malloc(sizeof(char*));

    Node* testNode5 = (Node*) malloc(sizeof(Node));
    testNode5->name = (char*) malloc(sizeof(char*));

    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    enqueue(queue, node4);
    enqueue(queue, node5);

    printQueue(queue);

    testNode1 = dequeue(queue);
    printf("%s\n", testNode1->name);
    testNode2 = dequeue(queue);
    printf("%s\n", testNode2->name);
    testNode3 = dequeue(queue);
    printf("%s\n", testNode3->name);
    testNode4 = dequeue(queue);
    printf("%s\n", testNode4->name);
    testNode5 = dequeue(queue);
    printf("%s\n", testNode5->name);

    return 0;

}


