#include "riffle.h"

int main()
{
    int L[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int* work = (int *)malloc(sizeof(int) * (sizeof(L) / sizeof(L[0])));
    riffle_once(&L[0], 13, sizeof(int), work);

    // char* greek[12] = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu" };    
    // char* work_greek[12] = {};
    // riffle_once(&greek[0], 12, sizeof(greek[0]), &work_greek[0]);

    // output of shuffled numbers. 
    int i;
    for(i = 0; i < 12; i++)
        printf("num: %d\n", *work++);
}

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
            break;
        }
        if(right == end)
        {
            *work_ptr = *right;
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
}
