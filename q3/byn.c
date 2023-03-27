#include "byn.h"

int main(int argc, char** argv)
{
    int i;
    int Nplayers;
    int games;
    
    if(argc > 2)
    {
        Nplayers = atoi(argv[1]);
        games = atoi(argv[2]);
        
        printf("RUNNING WITH VALUES TAKEN FROM COMMAND LINE ARGUMENTS!\n");
        for(i = 2; i <= Nplayers; i++)
        {
            STAT* stat = statistics(i, games);
            printf("Game with [%d] players. MIN: %d    AVG: %d    MAX: %d\n", i, stat->shortest, stat->average, stat->longest);
            free(stat);
        }
    }
    else
    {
        // command line arguments were not supplied
        printf("COMMAND LINE ARGUMENTS NOT SUPPLIED, RUNNING WITH ARGS FROM CA SPEC!\n");
        for(i = 2; i <= 10; i++)
        {
            STAT* stat = statistics(i, 100);
            printf("Game with [%d] players. MIN: %d    AVG: %d    MAX: %d\n", i, stat->shortest, stat->average, stat->longest);
            free(stat);
        }
    }

    return 0;
}

STAT* statistics(int Nplayers, int games)
{
    int i;

    // creating deck to play with
    int deck[52];
    int* deck_ptr = deck;
    for(i = 0; i < 52; i++)
        *deck_ptr++ = (i % 13) + 2; // 52 card deck, 2-14 in each suit.

    // gsl install needed for this function 
    shuffle(deck, 52, time(0));
    
    int* stats = (int*)malloc(sizeof(int)*games);
    int* ptr = stats;
    for(i = 0; i < games; i++)
        stats[i] = beggar(Nplayers, deck, 0);

    // finding smallest
    int smallest = *ptr;
    for(i = 0, ptr = stats; i < games; i++, ptr++)
    {
        if(*ptr < smallest)
            smallest = *ptr;
    }

    // finding average
    ptr = stats;
    int total = 0;
    for(i = 0; i < games; i++)
        total += *ptr++;

    int average = total / games;

    // finding largest
    ptr = stats;
    int largest = *ptr;
    for(i = 0; i < games; i++)
    {
        if(*ptr > largest)
            largest = *ptr;
    }

    free(stats);

    STAT* res = malloc(sizeof(STAT));
    res->shortest = smallest;
    res->average = average;
    res->longest = largest;

    return res;
}
