#include "riffle.h"

void riffle_once(void* L, int len, int size, void* work)
{
    // work pointer to set values in work
    char* work_ptr = work;

    // Setting pointers to the start and end of the list
    char* start = L;
    char* end = start + ((len - 1) * size);
    
    // Find the centre point of the list
    int centre = len / 2;
    
    // Setting left and right pointers
    char* left = start + ((centre - 1) * size);
    char* right = start + (centre * size);
    
    // riffling
    srand(time(0));
    while(1)
    {
        if(left == start)
        {
            *work_ptr = *left;
            work_ptr += size;
            break;
        }
        if(right == end)
        {
            *work_ptr = *right;
            work_ptr += size;
            break;
        }

        /* increase pointers by size */
        int choice = rand() % 2;
        if(choice)
        {
            *work_ptr = *left;
            work_ptr += size;
            left -= size;
        } else {
            *work_ptr = *right;
            work_ptr += size;
            right += size;
        }
    }

    
    // adding remaining cards to deck
    if(right == end)
    {
        while(left != start)
        {
            *work_ptr = *left;
            work_ptr += size;
            left -= size;
        }
        *work_ptr = *left;
    } else{
        while(right != end)
        {
            *work_ptr = *right;
            work_ptr += size;
            right += size;
        }
        *work_ptr = *right;
    }

    // Copy into L
    for(start = L, work_ptr = work; start <= end;)
    {
        *start = *work_ptr;
        start += size;
        work_ptr += size;
    }
}

void riffle(void* L, int len, int size, int N)
{
    void* work = malloc(size * len);
    
    int i;
    for(i = 0; i < N; i++)
    {
        riffle_once(L, len, size, work);
    }

    free(work);
}

int check_shuffle(void* L, int len, int size, int (*cmp)(void *, void *))
{
    // pointer to L
    char* L_ptr;
    
    // Will store original list
    char* base = malloc(size * len);
    char* base_ptr = base;

    // copying L into base
    memcpy(base, L, (len*size));
    
    L_ptr = L;
    // riffle L
    riffle(L, len, size, 30);

    // Check that they are the same using cmp function
    int i;
    int same;
    for(i = 0, L_ptr = L; i < len; i++, L_ptr += size)
    {
        same = 0;
        int j;
        for(j = 0, base_ptr = base; j < len; j++, base_ptr += size)
        {
            if(cmp(L_ptr, base_ptr) == 0)
            {
                same = 1;
                break;
            }
        }
        if(!same)
        {
            free(base);
            return same;
        }
    }
    free(base);
    return same;
}

int cmp(void* first, void* second)
{
    int* i1 = (int *)first;
    int* i2 = (int *)second;
    return *i1 == *i2;
}

int cmp_ints(int* first, int* second)
{
    if(*first == *second)
        return 0;
    else if(*first > *second)
        return 1;
    else
        return -1;
}

int cmp_strings(char* first, char* second)
{
    return strcmp(first, second);
}
