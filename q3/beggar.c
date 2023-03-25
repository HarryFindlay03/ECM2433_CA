#include "beggar.h"
#include "shuffle.h" // needed for Richard wrote shuffling using GSL.

typedef struct card
{
    int val;
    struct card *nextCard;
    struct card *prevCard;
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
    
    int result = beggar(5, deck, 0);

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
        players[i].bottom->prevCard = NULL;
        players[i].top = &playing_deck[i];
    }
    for(; i < (52 - Nplayers); i++) // dealing out the bulk of the cards
    {
        CARD* temp = players[i % Nplayers].top;
        players[i % Nplayers].top->nextCard = &playing_deck[i];
        players[i % Nplayers].top = &playing_deck[i];
        // setting previous card to (previous) top
        players[i % Nplayers].top->prevCard = temp;
    }
    for(; i < 52; i++) // setting the remaining cards and nextCard pointer to null
    {
        CARD* temp = players[i % Nplayers].top;
        players[i % Nplayers].top->nextCard = &playing_deck[i];
        players[i % Nplayers].top = &playing_deck[i];
        players[i % Nplayers].top->prevCard = temp;
        players[i % Nplayers].top->nextCard = NULL;
    }

    printf("TESTING => bottom card: %p, bottom next card: %p bottom previous card: %p\n", players[0].bottom, players[0].bottom->nextCard, players[0].bottom->prevCard);
    players[0].bottom = players[0].bottom->nextCard;
    printf("TESTING => bottom card: %p, bottom next card: %p bottom previous card: %p\n", players[0].bottom, players[0].bottom->nextCard, players[0].bottom->prevCard);
    
    players[0].bottom = players[0].bottom->nextCard;
    printf("TESTING => bottom card: %p, bottom next card: %p bottom previous card: %p\n", players[0].bottom, players[0].bottom->nextCard, players[0].bottom->prevCard);

    return 0;
}
