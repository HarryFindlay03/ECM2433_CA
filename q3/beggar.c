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

typedef struct table
{
    struct card *top;
    struct card *bottom;
} TABLE;

int main()
{
    // Creating a deck of cards
    int deck[52];

    int i;
    int* deck_ptr = deck;
    for(i = 0; i < 52; i++)
        *deck_ptr++ = (i % 13) + 2; // 52 card deck, 2-14 in each suit.
   
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


    // MAIN GAME PLAY
    int count = 1;
    TABLE* table = (TABLE *)malloc(52 * sizeof(CARD));

    // player 0 starts the game
    table->top = players[0].top;
    table->bottom = players[0].top;
    table->bottom->nextCard = table->top;

    // removing a card off of top of player 0's hand.
    players[0].top = players[0].top->prevCard;

    while(1)
    {
        if(table->top->val == 11) // jack is hit
        {

        }
        else if(table->top->val == 12) // queen is hit
        {

        }
        else if(table->top->val == 13) // king is hit
        {

        }
        else if(table->top->val == 14) // ace is hit
        {

        }

        // adding card to table
        CARD* temp = table->top;
        printf("TEMP: %p\n", temp);
        table->top->nextCard = players[count % Nplayers].top;
        table->top = players[count % Nplayers].top;

        
        // removing card from player hand
        players[count % Nplayers].top = players[count % Nplayers].top->prevCard;
        players[count % Nplayers].top->nextCard = NULL;
        
        if(players[count % Nplayers].top == players[count % Nplayers].bottom)
        {
            printf("GAME OVER on player [%d]\n", count % Nplayers);
            table->top->nextCard = NULL;

            while(!(table->bottom->nextCard == NULL))
            {
                printf("TABLE, current address: %p  next address: %p\n", table->bottom, table->bottom->nextCard);
                table->bottom = table->bottom->nextCard;
            }

            for(i = 0; i < Nplayers; i++)
            {
                while(!(players[i].bottom->nextCard == NULL))
                {
                    printf("Player [%d] Hand: Current address: %p  Next Card address: %p Previous card address: %p\n",i,  players[i].bottom, players[i].bottom->nextCard, players[i].bottom->prevCard);
                    players[i].bottom = players[i].bottom->nextCard;
                }
                printf("Player [%d] Hand: Current address: %p  Next Card address: %p Previous card address: %p\n",i,  players[i].bottom, players[i].bottom->nextCard, players[i].bottom->prevCard);
            }
            break;
        }

        count++;
    }

    return 0;
}

