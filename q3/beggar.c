#include "beggar.h"
#include "shuffle.h" // needed for Richard wrote shuffling using GSL.

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

    // creating players
    PLAYER* players = (PLAYER*)malloc(sizeof(PLAYER)*Nplayers);
    for(i = 0; i < Nplayers; i++)
    {
        players[i].id = i;
        players[i].head = NULL;
    }

    // for each card in deck append to players
    for(i = 0; i < 52; i++)
        append(&(players[i % Nplayers].head), deck[i]);
   
    // TESTING
    for(i = 0; i < Nplayers; i++)
    {
        while(players[i].head->nextCard != NULL)
        {
            printf("PLAYER [%d] holds card: %d\n", i, players[i].head->val);
            players[i].head = players[i].head->nextCard;
        }
        printf("PLAYER [%d] holds card: %d\n", i, players[i].head->val);
    }

    return 0;
}

void append(CARD** head, int val)
{
    // allocate new card
    CARD* new_card = (CARD *)malloc(sizeof(CARD));

    CARD* last = *head;
    
    new_card->val = val;
    new_card->nextCard = NULL;

    // If the list is empty make the new node as head
    if(*head == NULL)
    {
        new_card->prevCard = NULL;
        *head = new_card;
        return;
    }

    // Else traverse the list until the last node
    while(last->nextCard != NULL)
        last = last->nextCard;

    // change the next node of last node, and set new nodes prev
    last->nextCard = new_card;
    new_card->prevCard = last;

    return;
}

void push(CARD** head, int val)
{
    // allocate node
    CARD* new_card = (CARD *)malloc(sizeof(CARD));

    new_card->val = val;

    new_card->nextCard = (*head);
    new_card->prevCard = NULL;
    
    // make the old heads previous new_card if head is not null
    if((*head) != NULL)
        (*head)->prevCard = new_card;

    (*head) = new_card;
}

CARD* gen_cards(int* start, int* end)
{
    CARD* cards = (CARD *)malloc((end - start));
    CARD* card_ptr = cards;

    printf("Start val: %d    end val: %d\n", *start, *end);

    for(;start < end;)
        card_ptr++->val = *start++;
    
    int len = (end - start);
    printf("LEN VALUE: %d\n", len);
    cards[0].prevCard = NULL;
    cards[0].nextCard = &cards[1];

    int i;
    for(i = 1; i < (len - 1); i++)
    {
        cards[i].prevCard = &cards[i-1];
        cards[i].nextCard = &cards[i+1];
    }
    cards[len-1].prevCard = &cards[len-2];
    cards[len-1].nextCard = NULL;

    card_ptr = cards;
    for(i = 0; i < len; i++)
        printf("TESTING GEN CARDS: %d\n", card_ptr++->val);

    return cards;
}

int is_special(int* card)
{
    if(*card == 11)
        return 1;
    else if(*card == 12)
        return 2;
    else if(*card == 13)
        return 3;
    else if(*card == 14)
        return 4;

    return 0;
}
