#include "quality.h"

int main()
{
    // testing quality function
    int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Quality of list 1..10: %f\n", quality(nums, 10));

    int better[10] = {5, 4, 6, 3, 7, 8, 9, 2, 10, 1};
    printf("Quality of list with better shuffle: %f\n", quality(better, 10));

    // testing average quality function
    int N = 50;
    int shuffles = 15;
    int trials = 30;
    average_quality(N, shuffles, trials);
}

