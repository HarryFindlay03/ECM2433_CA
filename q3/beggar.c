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
    int j;
    // creating CARD deck
    CARD playing_deck[52];
    for(i = 0; i < 52; i++)
        playing_deck[i].val = deck[i];

    // creating players
    PLAYER players[Nplayers];
    for(i = 0; i < Nplayers; i++)
        players[i].id = i;

    // dealing out cards
    for(i = 0; i < Nplayers; i++) // setting bottom and top pointers
    {
        players[i].bottom = &playing_deck[i];
        players[i].top = &playing_deck[i];
    }
    for(j = i; i < ((52 / Nplayers) * Nplayers); i++, j++) // dealing out the bulk of the cards
    {
        players[i % Nplayers].top->nextCard = &playing_deck[j];
        players[i % Nplayers].top = &playing_deck[j];
    }
    for(; j < 52; j++) // setting the remaining cards and nextCard pointer to null
    {
        players[j & Nplayers].top = &playing_deck[j];
        players[j % Nplayers].top->nextCard = NULL;
    }

    // Checking that the dealing worked
    for(i = 0; i < Nplayers; i++)
    {
        while(!(players[i].bottom->nextCard == NULL))
        {
            printf("Player [%d] Hand: %d\n", i, players[i].bottom->val);
            players[i].bottom = players[i].bottom->nextCard;
        }

        printf("Player [%d] Hand: %d\n", i, players[i].bottom->val);
    }

    return 0;
}
