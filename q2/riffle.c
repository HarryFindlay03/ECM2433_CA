#include "riffle.h"

// int main()
// {
//     int L[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
//     // int* work = (int *)malloc(sizeof(int) * (sizeof(L) / sizeof(L[0])));
//     // riffle_once(&L[0], 13, sizeof(int), work);
//     //
//     // char* greek[12] = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu" };
//     // char* work_greek = (char *)malloc(sizeof(greek) / sizeof(greek[0]));
//     // riffle_once(&greek[0], 12, sizeof(greek[0]), work_greek);
//     //
//     // // output of shuffled numbers. 
//     // int i;
//     // for(i = 0; i < 13; i++)
//     //     printf("num: %d\n", L[i]);
//     //
//     // // output of shuffled greek
//     // for(i = 0; i < 12; i++)
//     //     printf("word: %s\n", greek[i]);
//     //
//     // free(work);
//     // free(work_greek);
//     
//     // riffle(&L[0], 13, sizeof(int), 10);
//     // // output of shuffled numbers. 
//     // int i;
//     // for(i = 0; i < 13; i++)
//     //     printf("num: %d\n", L[i]);
//
//     if(check_shuffle(&L[0], 13, sizeof(int), &cmp))
//         printf("Shuffle works correctly!\n");
//     else
//         printf("Shuffle does not work :(");
//
//     return 0;
// }

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

    // Copy original into base
    // int i;
    // for(i = 0, L_ptr = L, base_ptr = base; i < len; i++)
    // {
    //     printf("base pointer: %s\n", base_ptr);
    //     printf(" L pointer: %s\n", L_ptr);
    //     *base_ptr = *L_ptr;
    //     base_ptr += size;
    //     L_ptr += size;
    // }
    int i;
    char* start = L;
    char* end = L + ((len-1) * size);

    while(start <= end)
    {
        *base_ptr = *start;
        start += size;
        base_ptr += size;
    }
    
    // riffle L
    riffle(L, len, size, 30);

    // Check that they are the same using cmp function
    int same;
    for(i = 0, L_ptr = L; i < len; i++, L_ptr += size)
    {
        same = 0;
        int j;
        for(j = 0, base_ptr = base; j < len; j++, base_ptr += size)
        {
            if(cmp(L_ptr, base_ptr))
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
