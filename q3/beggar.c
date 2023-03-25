#include "beggar.h"
#include "shuffle.h" // needed for Richard wrote shuffling using GSL.

typedef struct card
{
    int val;
    struct card *nextCard;
} CARD;

typedef struct player
{
    int id;
    struct card *top;
    struct card *bottom;
} PLAYER;

int main()
{
    // Creating a deck of cards
    int deck[52];

    int i;
    int* deck_ptr = deck;
    for(i = 0; i < 52; i++)
        *deck_ptr++ = (i % 13) + 2; // 52 card deck, 2-14 in each suit.

    // for(i = 0, deck_ptr = deck; i < 52; i++, deck_ptr++)
    //     printf("DECK: %d\n", *deck_ptr);
    
    // gsl library install needed for this
    // shuffle(deck, 52,  time(0));
    
    int result = beggar(4, deck, 0);

}

int beggar(int Nplayers, int *deck, int talkative)
{
    int i;
    // creating CARD deck
    CARD playing_deck[52];
    for(i = 0; i < 51; i++)
    {
        playing_deck[i].val = deck[i];
        playing_deck[i].nextCard = &playing_deck[i+1];
        printf("TESTING curr address: %p  val: %d  next card address: %p\n", &playing_deck[i], playing_deck[i].val, playing_deck[i].nextCard);
    }
    playing_deck[51].val = deck[51];
    playing_deck[51].nextCard = NULL;

    return 0;
}
