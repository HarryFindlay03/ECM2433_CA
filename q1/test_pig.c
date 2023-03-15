#include "test_pig.h"

int main()
{
    char *words[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    int i;
    for(i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        printf("%s => %s\n", words[i], pig(words[i]));
    }
    return 0;
}

