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
    
    int result = beggar(5, deck, 1);

}

int beggar(int Nplayers, int *deck, int talkative)
{
    int i;
    int j;

    // creating pile -> MAX could be 52 cards.
    PILE* pile = malloc(sizeof(CARD) * 52);
    pile->head = NULL;

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
   
    // MAIN GAMEPLAY
    int count = 0;
    while(1)
    {
        // OUTPUT
        if(talkative)
        {
            PILE temp_pile = (*pile);
            PILE tail = temp_pile;
            printf("Pile: ");
            while(temp_pile.head != NULL)
            {
                printf(" %d", temp_pile.head->val);
                temp_pile.head = temp_pile.head->nextCard;
            }
            printf("\n");

            for(i = 0; i < Nplayers; i++)
            {
                PLAYER current_player = players[i];
                if(i == count % Nplayers)
                {
                    printf("*   %d: ", i);
                    while(current_player.head != NULL)
                    {
                        printf(" %d", current_player.head->val);
                        current_player.head = current_player.head->nextCard;
                    }
                    printf("\n");
                    continue;
                }
                printf("    %d: ", i);
                while(current_player.head != NULL)
                {
                    printf(" %d", current_player.head->val);
                    current_player.head = current_player.head->nextCard;
                }
                printf("\n");
            }
        }

        int penalty;
        if(pile->head != NULL)
            penalty = is_special(pile->head->val);

        // removing cards from current players hand as they 'recieved' the penalty card
        for(i = 0; i < penalty; i++)
        {
            push(&(pile->head), players[count % Nplayers].head->val);
            delete_node(&(players[count % Nplayers].head), players[count % Nplayers].head);

            if(players[count % Nplayers].head == NULL)
            {
                printf("GAME OVER\n");
                return 0;
            }

        }
        
        // if penalty occured, append pile to previous player, continue play with player who picked up the cards
        if(penalty)
        {
            // adding cards to previous player (player who played the penalty card)
            PILE* temp_head = pile; // for clearing the pile later
            
            while(pile->head->nextCard != NULL)
            {
                append(&(players[(count - 1) % Nplayers].head), pile->head->val);
                pile->head = pile->head->nextCard;
            }
            // append the final card
            append(&(players[(count - 1) % Nplayers].head), pile->head->val);

            // clear the pile
            while(temp_head->head->nextCard != NULL)
            {
                delete_node(&(temp_head->head), temp_head->head);
            }
            
            continue;
        }
        // add the head card onto the pile.
        push(&(pile->head), players[count % Nplayers].head->val);

        // remove a card from the linked list. 
        delete_node(&(players[count % Nplayers].head), players[count % Nplayers].head);

        if(players[count % Nplayers].head == NULL)
        {
            printf("GAME OVER on player [%d]\n", count % Nplayers);
            break;
        }
        count++;
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

void append_pile(CARD** player_head, CARD* pile_head)
{
    // traverse until last node
    CARD* last = *player_head;
    while(last->nextCard != NULL)
        last = last->nextCard;

    // set next node of last card to pile head
    last->nextCard = pile_head;
    pile_head->prevCard = last;

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

void delete_node(CARD** head, CARD* del)
{
    if(*head == NULL || del == NULL)
        return;

    // if node to be deleted is head node
    if(*head == del)
        *head = del->nextCard;

    // change next only if node to be deleted is not NULL
    if(del->nextCard != NULL)
        del->nextCard->prevCard = del->prevCard;

    // change prev only if node to be deleted is not the first nodes
    if(del->prevCard != NULL)
        del->prevCard->nextCard = del->nextCard;

    free(del);
    return;
}

int is_special(int card)
{
    if(card== 11)
        return 1;
    else if(card == 12)
        return 2;
    else if(card == 13)
        return 3;
    else if(card == 14)
        return 4;

    return 0;
}
