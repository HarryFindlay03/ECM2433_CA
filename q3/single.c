#include "single.h"

int main(int argc, char** argv)
{
    // taking command line arguments
    int num_players;
    if(argc > 1)
        num_players = atoi(argv[1]);

    // Creating a deck of cards// Creating a deck of cards
    int deck[52];

    int i;
    int* deck_ptr = deck;
    for(i = 0; i < 52; i++)
        *deck_ptr++ = (i % 13) + 2; // 52 card deck, 2-14 in each suit.

    // gsl library install needed for this
    // shuffle(deck, 52,  time(0));

    int result = beggar(num_players, deck, 1);
    
    return 0;
}
