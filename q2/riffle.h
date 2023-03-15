#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void riffle_once(void* L, int len, int size, void* work);
void riffle(void* L, int len, int size, int N);
int check_shuffle(void* L, int len, int size, int (*cmp)(void*, void*));
int cmp(void*, void*);
