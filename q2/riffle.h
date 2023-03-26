#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void riffle_once(void* L, int len, int size, void* work);
void riffle(void* L, int len, int size, int N);
int check_shuffle(void* L, int len, int size, int (*cmp)(void*, void*));
int cmp_ints(int*, int*);
int cmp_strings(char**, char**);

float quality(int*, int);
void average_quality(int, int, int);
float mean(float*, int);
