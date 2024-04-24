// Imports
#include "hashmap.h"

// Constants

// Max length of a name of a path
// const int MAX_NAME_SIZE = 256;

// Prime number used to space out hash values in the hash function
// Used to avoid clumping in the hashmap
const int PRIME_MULTI_CONST = 31;

/* 
Function to instantiate a hashmap and allocate memory
@param map:Hashmap** pointer to Hashmap pointer
@param size:int represents the size of the hashmap
*/
void instantiateHashmap(Hashmap** map, int size) {
    *map = (Hashmap*) malloc(sizeof(Hashmap));
    (*map)->paths = (Path**) malloc(sizeof(Path*) * size);
    (*map)->size = size;
}

/*
Function to instantiate path object
@param label:char* item label
@param value:int value of the item
@param weight:int weight of the item
@return returns a pointer to the Path object
*/
Path* createPath(char* label, int value, int weight) {
    Path* outputPath = (Path*) malloc(sizeof(Path));
    outputPath->name = (char*) malloc(sizeof(char) * 255);
    strcpy(outputPath->name, label);
    outputPath->value = value;
    outputPath->weight = weight;
    return outputPath;
}

/*
Function to hash a string and return a hashed int index
@param name:char* string that neeeds to be hashed 
@return returns the hashed int value
*/
unsigned int hash(char* name) {
    int length = strlen(name);
    unsigned int hashValue = 0;

    for (int i = 0; i < length; i++) {
        hashValue = (hashValue * PRIME_MULTI_CONST) + name[i];
    }
    return hashValue;
}

/*
Function to insert a path into a Hashmap of paths
@param map:Hashmap* Hashmap object that is being modified
@param key:char* key of the object being inserted
@param value:int value of the path
@param weight:int weight of the objects included in the path
*/
void insert(Hashmap* map, char* key, int value, int weight) {
    unsigned int index = hash(key) % map->size;

    Path* newPath = (Path*) malloc(sizeof(Path));
    newPath->name = (char*) malloc(sizeof(char) * 255);
    strcpy(newPath->name, key);
    newPath->value = value;
    newPath->weight = weight;
    newPath->next = NULL;

    if(map->paths[index] == NULL) {
        map->paths[index] = newPath;
    } else {
        int flag = 0;
        Path* current = map->paths[index];
        while(flag != 1) {
            if(current->next == NULL) {
                current->next = newPath;
                flag = 1;
            } else {
                current = current-> next;
            }
        }
    }
    
}

/*
Function to find a specified key in the provided hashmap
@param map:Hashmap* hashmap that is being searched in 
@param key:char* key value that is being searched for
@return returns a pointer to the Path object that was found 
if no object was found, then NULL will be returned
*/
Path* find(Hashmap* map, char* key) {
    unsigned int index = hash(key) % map->size;
    Path* current = map->paths[index];

    while (current != NULL) {
	printf("current = %s, key = %s\n", current->name, key);

        if (strcmp(current->name, key) == 0) {
            return current;
        }
        if(current->next != NULL && current->next->name != NULL) {
            current = current->next;
        } else {
            current = NULL;
        }
        
    }

    return NULL;
}

/*
Function to print out a Hashmap to the console
@param map:Hashmap* Hashmap that is being printed
*/
void printHashmap(Hashmap* map) {
    for(int i = 0; i < map->size; i++) {
        if(map->paths[i] != NULL) {
            Path* current = map->paths[i];
            if(current->next == NULL) {
                printf("%s\n", current->name);
            } else {
                while(current != NULL) {
                    printf("%s ", current->name);
                    current = current->next;
                }
                printf("\n");
            }
    
        } else {
            printf("---------\n");
        }
        
    }
}

void freeList(Path* head) {
    Path* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
}

void freeHashmap(Hashmap* map) {
    for(int i = 0; i < map->size; i++) {
        if(map->paths[i] != NULL) {
            freeList(map->paths[i]);
        }     
    }
}

int hashmapMain() {
    Hashmap* map;
    instantiateHashmap(&map, 10);

    insert(map, "1", 10, 21);
    insert(map, "1-5", 10, 21);
    insert(map, "1-3", 10, 21);
    insert(map, "3", 10, 21);
    insert(map, "3-5", 10, 21);
    insert(map, "3-7", 10, 21);
    insert(map, "5", 10, 21);
    insert(map, "5-7", 10, 21);
    insert(map, "7", 10, 21);
    insert(map, "1-3-5-7", 10, 21);
    insert(map, "7-9", 10, 21);
    insert(map, "7", 10, 21);
    insert(map, "5-7-9", 10, 21);
    insert(map, "1-3-5-7-9", 10, 21);

    Path* result = (Path*) malloc(sizeof(Path));
    result = find(map, "7");

    printHashmap(map);

    printf("result = %s\n", result->name);

    freeHashmap(map);

    return 0;
}
