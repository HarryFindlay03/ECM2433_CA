#include "demo_shuffle.h"

int main()
{
    int L[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int L_checkshuffle[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int len_L = sizeof(L) / sizeof(L[0]);
    int* ptr;

    // Original L array
    printf("Original array: ");
    int i;
    for(i = 0, ptr = L; i < len_L-1; i++, ptr++)
        printf("%d, ", *ptr);
    printf("%d\n\n", *ptr);

    // Shuffle L
    // arr, len of arr, size of each item in the array, how many times to shuffle
    riffle(&L[0], len_L, sizeof(int), 30);

    // Outputting the shuffled array
    printf("Shuffled array: ");
    for(i = 0; i < len_L-1; i++)
        printf("%d, ", L[i]);
    printf("%d\n\n", L[len_L-1]);

    // // Shuffling greek words
    char* greek[12] = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu" };
    char* greek_checkshuffle[12] = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu" };
    int len_greek = sizeof(greek) / sizeof(greek[0]);

    printf("Original array: ");
    for(i = 0; i < len_greek-1; i++)
        printf("%s, ", greek[i]);
    printf("%s\n\n", greek[len_greek-1]);

    riffle(&greek[0], len_greek, sizeof(greek[0]), 30);

    printf("Shuffled array: ");
    for(i = 0; i < len_greek-1; i++)
        printf("%s, ", greek[i]);
    printf("%s\n\n", greek[len_greek-1]);
    
    if(check_shuffle(&L_checkshuffle[0], len_L, sizeof(int), &cmp_ints))
        printf("Shuffling nums: SUCESS\n");
    else
        printf("Shuffling nums: FAILURE\n");
    
    // if(check_shuffle(&greek_checkshuffle[0], len_greek, sizeof(greek[0]), &cmp_strings))
    //     printf("Shuffling words: SUCCESS\n");
    // else
    //     printf("Shuffling words: FAILURE\n");
    return 0;
}

