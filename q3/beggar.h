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
    struct card *head;
} PILE;

int beggar(int, int*, int);
void append(CARD**, int);
void append_pile(CARD**, CARD*);
void push(CARD**, int);
void delete_node(CARD**, CARD*);
int is_special(int);

void output(PILE*, PLAYER*, int);
