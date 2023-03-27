#include <stdio.h>
#include <string.h>
#include "pig.h"

int main()
{
    printf("=============================\n");
    printf("ENGLISH TO PIGLATIN CONVERTER\n");
    printf("=============================\n");
    printf("\n\n");

    int go = 1;
    while(go) {
        char str[250]; 

        printf("Enter text to convert to piglatin (press return to exit): ");
        fgets(str, sizeof(str), stdin);

        // if an empty line has been inputted then exit 
        char* ptr;
        ptr = str;
        if(*ptr == '\n' | *ptr == '\r')
            break;

        // remove the new line at the end of a valid input and replace with null terminator.       
        for(; *ptr; ptr++)
        {
            if(*ptr == '\n' | *ptr == '\r')
                *ptr = '\0';
        }

        char s[2] = " ";
        char* token;
        token = strtok(str, s);

        printf("\nOUTPUT: ");
        while(token != NULL)
        {
            char* pig_word = pig(token);
            printf("%s ", pig_word);
            token = strtok(NULL, s);
        }
        printf("\n\n\n");
    }
    
    printf("\n\nThank you, exiting...\n");
    return 0;
}
