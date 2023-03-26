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

typedef struct pile
{
    struct card *top;
} PILE;

CARD* gen_cards(int*, int);

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
    int count = 0;
    int* pile = (int *)malloc(sizeof(int) * 52);
    int* start_pile = pile;
    int* end_pile = pile;

    while(1)
    {
        if(*end_pile == 11) //jack
        {
            printf("TESTING\n");
            *end_pile = players[count % Nplayers].top->val;
            CARD* to_add = gen_cards(pile, ((end_pile - start_pile) / sizeof(int)));
            end_pile = pile;

            // adding the cards to the back of the player befores hand
            CARD top_of_pile;
            while(!(to_add->nextCard == NULL))
                to_add++;

            players[(count % Nplayers)-1].bottom->prevCard = to_add;
            count++;
            continue;
        }
        else if(*end_pile == 12) //queen
        {

        }
        else if(*end_pile == 13) //king
        {

        }
        else if(*end_pile == 14) //ace
        {

        }
        end_pile++;

        // adding cards to pile 
        *end_pile = players[count % Nplayers].top->val;

        // removing card from player hand
        players[count % Nplayers].top = players[count % Nplayers].top->prevCard;
        players[count % Nplayers].top->nextCard = NULL;

        if(players[count % Nplayers].top == players[count % Nplayers].bottom)
        {
            printf("GAME OVER!\n");
            break;
        }
        
        count++;
    }

    return 0;
}

CARD* gen_cards(int* pile, int len)
{
    CARD* cards = (CARD *)malloc(len * sizeof(CARD));
    int i;
    for(i = 0; i < len; i++)
        cards[i].val = *pile++;

    cards[0].prevCard = NULL;
    cards[0].nextCard = &cards[1];
    for(i = 1; i < len - 1; i++)
    {
        cards[i].prevCard = &cards[i-1];
        cards[i].nextCard = &cards[i+1];
    }
    cards[len-1].prevCard = &cards[len-2];
    cards[len-1].nextCard = NULL;

    return cards;
}
