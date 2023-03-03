#include "test_pig.h"

int main()
{
    char *words[] = {"happy", "duck", "glove", "evil", "eight", "yowler", "crystal"};
    int i;
    for(i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        printer(words[i]); 
    }
    return 0;
}

void printer(char* word)
{
    char* word_ptr = word;
    char* return_word = pig(word);
    char* return_word_ptr = return_word;

    for(;*word_ptr;)
        printf("%c", *word_ptr++);

    printf(" => ");

    for(;*return_word_ptr;)
        printf("%c", *return_word_ptr++);

    printf("\n");

    free(return_word);
}
