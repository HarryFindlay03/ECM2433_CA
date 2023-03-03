#include "pig.h"

int check_vowel(char* c)
{
    if(*c == 'A' | *c == 'E' | *c == 'I' | *c == 'I' | *c == 'O' | *c == 'U')
    {
        return 1;
    }
    if(*c == 'a' | *c == 'e' | *c == 'i' | *c == 'o' | *c == 'u')
    {
        return 1;
    }
    return 0;
}

char* pig(char* word)
{
    char* q;
    int size_word = 0;

    // Finding the size of the word 
    for(q = word; *q; q++)
        size_word++;

    char* return_word;

    if(!(return_word = (char*)malloc(sizeof(char) * (size_word + 3))))
    {
        printf("ERROR in allocating memory !");
        exit(-1);
    }
    char* x; // return_word pointer 
    
    q = word;

    if(!check_vowel(q))
    {
        // Removing initial constanants and saving them
        char* removed;
        if(!(removed = (char*)malloc(sizeof(char)*size_word)))
        {
            printf("ERROR in allocating memory!");
            exit(-1);
        }

        char* y = removed;
        *y++ = *q++;

        while(!(check_vowel(q)))  
        {
            if(*q == 'Y' | *q == 'y')
                break;

            *y++ = *q++;
        }

        // Adding the remaining original word to return_word
        for(x = return_word; *q;)
            *x++ = *q++;
        
        // adding removed constanants to the end of return_word
        for(y = removed; *y;)
            *x++ = *y++;
       
        free(removed);

        // appending "ay" to the end of return_word
        char* append_word = "ay";
        for(q = append_word; *q;)
            *x++ = *q++;
        
        return return_word;
    } else {
        // It is a vowel to start
        for(x = return_word;*q;)
            *x++ = *q++;

        char* append_word = "way";
        for(q = append_word; *q;)
            *x++ = *q++;

        return return_word;
    }
}
