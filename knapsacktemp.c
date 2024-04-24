// imports
#include "knapsack.h"

/*
Function to print an item set to the console
@param labels:char** list of strings representing the item labels
@param weights:int* array of integers representing the weight of each item
@param values:int* array of integers representing the value of each item
@param size:int size of the item set
*/
void printListSet(char** labels, int* weights, int* values, int size) {
    printf("Itemset (%d)\n", size);
    printf("------------------------------------------\n");
    for(int i = 0; i < size; i++) {
        printf("[%s], weight = [%d], value = [%d]\n", labels[i], weights[i], values[i]);
    }
    printf("------------------------------------------\n");
}

/*
Function to instantiate an itemset
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
void instantiateItemset(char*** labels, int** values, int** weights, int size) {
    *values = (int*) malloc(size * sizeof(int));
    *weights = (int*) malloc(size * sizeof(int));
    *labels = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        (*labels)[i] = malloc(MAX_LABEL_LENGTH * sizeof(char));
    } 
}

/*
Function to free an itemset
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
void freeItemset(char*** labels, int** values, int** weights, int size) {
    free(*weights);
    free(*values);
    for(int i = 0; i < size; i++) {
        free((*labels)[i]);
    }

    free(*labels);
}

/*
Function to weight each item's value by the ratio of their weight to the max weight.
@param weightedValuesArray:float* pointer to array for weighted values to be stored
@param weights:int* array of integers representing item weights
@param values:int* array of integers representing item values
@param size:int integer representing the size of the item set
*/
void calculateWeightedValues(float* weightedValuesArray, int* weights, int* values, int size) {
    for(int i = 0; i < size; i++) {
        weightedValuesArray[i] = (MAX_SOLUTION_WEIGHT / (weights)[i]) * (values)[i];
    }
}

/*
Function that will create a z-score for each item based on the weight value and filter
out items below the threshold
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
*/
int filterItemsByWeightedValue(char*** labels, int** values, int** weights, int size) {
    int newSize = 0;
    char** newLabels;
    int* newValues;
    int* newWeights;

    float* weightedValues = (float*) malloc(sizeof(float) * size);
    calculateWeightedValues(weightedValues, *weights, *values, size);

    float* zScores = (float*) malloc(sizeof(float) * size);
    zScores = calculateZScores(weightedValues, size);

    for(int i = 0; i < size; i++) {
        if(zScores[i] >= WV_ZSCORE_THRESHOLD) {
            newSize++;
        }
    }

    instantiateItemset(&newLabels, &newValues, &newWeights, newSize);

    int current = 0;
    for(int i = 0; i < size; i ++) {
        if(zScores[i] >= WV_ZSCORE_THRESHOLD) {
            strcpy(newLabels[current],(*labels)[i]);
            newWeights[current] = (*weights)[i];
            newValues[current] = (*values)[i];
            current++;
        }
    }

    freeItemset(labels, values, weights, size);
    free(weightedValues);
    free(zScores);
    
    *labels = newLabels;
    *weights = newWeights;
    *values = newValues;

    return newSize;
}


/*
Function to calculate the weight attributable to a route
@param map:Hashmap* pointer to hashmap
@param route:char* route string
@param weights:int* array of weights for each item
@param values:int* array of values for each item
@param solutions:Path** array of Path pointers  to be filled in
@param solutionsCount:int* pointer to integer representing number of valid solutions
@return returns weight of the route
*/
int calculateRoute(Hashmap* map, char* route, int* weights, int* values, Path** solutions, int* solutionsCount) {
    if(strlen(route) == 0) {
        return 0;
    }

    Path* path;
    path = find(map, route);

    if(path != NULL) {
        return path->weight;
    } 
    else {
        int count = 0;
        int weight = 0;
        int value = 0;
        int* objects = splitPath(route, '-', &count);

        char* partialPath = convertArrayToString(objects, "-", count - 1);
        path = find(map, partialPath);


        if(path != NULL && count > 2) {
            weight = path->weight + weights[objects[count - 1]];
            value = path->value + values[objects[count - 1]];
        } else {
            for(int i = 0; i < count; i++) {
                weight += weights[objects[i]];
                value += values[objects[i]];
            }
        }

	solutions[(*solutionsCount)] = createPath(route, value, weight);

        ++(*solutionsCount);
        

        insert(map, route, value, weight);


        return weight;    
    }

    return -1;
}

/*
Function to calculate all routes that are valid but will stop moving forward when surpasses max weight
@param labels:char*** pointer to list of strings representing the item labels
@param values:int** pointer to array of integers representing the weight of each item
@param weights:int** pointer to array of integers representing the value of each item
@param size:int size of the item set
@param solutionsCount: int* pointer to int 
*/
Path** findValidRoutes(char** labels, int* weights, int* values, int size, int* solutionsCount) {
    Path** solutions = (Path**) malloc(sizeof(Path) * pow(2, (size + 2)));

    Hashmap* map;
    instantiateHashmap(&map, pow(size, 3));

    int currentPlace = 0;

    Queue* queue = (Queue*) malloc(sizeof(Queue));

    Node* startingNode = (Node*) malloc(sizeof(Node));
    startingNode->name = (char*) malloc(sizeof(char*) * 255);
    strcpy(startingNode->name, "");

    enqueue(queue, startingNode);

    while(currentPlace < size + 1) {
        char** exploredPaths = (char**) malloc(sizeof(char*) * pow(2, (size + 2)));
        int numPaths = 0;

        while(queue->head != NULL) {
            Node* currentNode = dequeue(queue);

            int weight = calculateRoute(map, currentNode->name, weights, values, solutions, solutionsCount);

            printf("{%s}, {%d}\n", currentNode->name, weight);

            if(weight <= MAX_SOLUTION_WEIGHT) {
                exploredPaths[numPaths] = (char*) malloc(sizeof(char*) * size * 2);
                strcpy(exploredPaths[numPaths], currentNode->name);
                numPaths++;
            }            

        }

        if(currentPlace < size) {
            for(int i = 0; i < numPaths; i++) {
                if(strlen(exploredPaths[i]) > 0) {
                    char* expandedPath = (char*) malloc(sizeof(char*) * size * 4 + 1);
                    strcat(expandedPath, exploredPaths[i]);
                    strcat(expandedPath, "-");
                    char* value = (char*) malloc(sizeof(char) * 255);
                    sprintf(value, "%d", currentPlace); 
                    strcat(expandedPath, value);

                    Node* node1 = (Node*) malloc(sizeof(Node));
                    node1->name = (char*) malloc(sizeof(char*) * size * 2);
                    strcpy(node1->name, exploredPaths[i]);

                    Node* node2 = (Node*) malloc(sizeof(Node));
                    node2->name = (char*) malloc(sizeof(char*) * size * 2);
                    strcpy(node2->name, expandedPath);

                    enqueue(queue, node1);
                    enqueue(queue, node2);
                } else {
                    char* expandedPath = (char*) malloc(sizeof(char*) * size * 4 + 1);
                    char* value = (char*) malloc(sizeof(char*) * 255);
                    sprintf(value, "%d", currentPlace); 
                    strcat(expandedPath, value);

                    Node* node1 = (Node*) malloc(sizeof(Node));
                    node1->name = (char*) malloc(sizeof(char*) * size * 2);
                    strcpy(node1->name, "");

                    Node* node2 = (Node*) malloc(sizeof(Node));
                    node2->name = (char*) malloc(sizeof(char*) * size * 2);
                    strcpy(node2->name, expandedPath);

                    enqueue(queue, node1);
                    enqueue(queue, node2); 
                }
            }
        }
        
        currentPlace++;
        for(int i = 0; i < numPaths - 1; i++) {
            free(exploredPaths[i]);
        }
        free(exploredPaths);
    }

    freeHashmap(map);
    free(map);

    return solutions;
}

/*
Main program function to run the application
*/
int main(int argc, char *argv[]) {
    FILE *file;
    int* val;
    int* wt;
    char** labels;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");

    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    int count = countLines(file);

    instantiateItemset(&labels, &val, &wt, count);

    parseItems(file, labels, val, wt);

    count = filterItemsByWeightedValue(&labels, &val, &wt, count);

    printListSet(labels, wt, val, count);

    int baseSolutionsCount = 0;
    int* solutionCount = &baseSolutionsCount;

    Path** solutions = findValidRoutes(labels, wt, val, count, solutionCount);

    printf("solutions = %d\n", *solutionCount);

    for(int i = 0; i < *solutionCount; i++) {
        printf("[solution = {%s}, weight = {%d}, value = {%d}]\n", (*(solutions[i])).name, (*(solutions[i])).weight, (*(solutions[i])).value);
    }

    for(int i = 0; i < *solutionCount; i++) {
        free(solutions[i]->name);
        free(solutions[i]);
    }

    freeItemset(&labels, &val, &wt, count);

    return 0;
}
