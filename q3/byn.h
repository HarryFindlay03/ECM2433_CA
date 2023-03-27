#include "beggar.h"

typedef struct stat
{
    int shortest;
    int average;
    int longest;
} STAT;

STAT* statistics(int, int);
