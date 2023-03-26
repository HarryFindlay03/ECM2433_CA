#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card
{
    int val;
    struct card *nextCard;
    struct card *prevCard;
} CARD;

typedef struct player
{
    int id;
    struct card *head;
} PLAYER;

typedef struct pile
{
    struct card *top;
} PILE;

int beggar(int, int*, int);
void append(CARD**, int);
CARD* gen_cards(int*, int*); 
int is_special(int*);
