all: main

main: hashmap.c knapsack.c fileoperations.c
	clang -Wall -Wextra -O0 -g hashmap.c knapsack.c fileoperations.c statmath.c listfuncs.c queuemodel.c -o knapsack -lm

