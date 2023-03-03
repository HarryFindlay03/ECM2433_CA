#include <stdio.h>
#include <string.h>
#include "pig.h"

int main()
{
    int go = 1;
    while(go) {
        char str[80]; 

        printf("Enter text to convert to piglatin (press return to exit): ");
        fgets(str, sizeof(str), stdin);

        // if an empty line has been inputted then exit 
        char* ptr;
        int size = 0;
        for(ptr = str; *ptr; ptr++)
            size++;
    
        // TODO: This might be different on windows !
        if(size == 1)
        {
            go = 0;
            break;
        }

        // remove the new line at the end of input and replace with null terminator.       
        for(ptr = str; *ptr; ptr++)
        {
            if(*ptr == '\n' | *ptr == '\r')
                *ptr = '\0';
        }

        char s[2] = " ";
        char* token;
        token = strtok(str, s);

        while(token != NULL)
        {
            char* pig_word = pig(token);
            for(;*pig_word;)
                printf("%c", *pig_word++);

            printf(" ");
            token = strtok(NULL, s);
        }
        printf("\n");
        size = 0;
    }
    
    printf("Thank you, exiting...\n");
    return 0;
}
