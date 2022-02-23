#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node_t* node_create(int *index)
{
    node_t *new = calloc(1, sizeof(node_t));

    if (new)
    {
        new->Nk = *index;
        new->next = NULL;
    }

    return new;
}


void person_free(node_t *node)
{
    free(node);
}

node_t* list_add_end(node_t *head, node_t *node)
{
    node_t *cur = head;

    if (!head)
        return node;

    for ( ; cur->next; cur = cur->next);
    cur->next = node;

    return head;
}
