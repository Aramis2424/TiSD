#ifndef NODE_H
#define NODE_H

#include "structures.h"

node_t* node_create(int *index);
void node_free(node_t *node);
node_t* list_add_end(node_t *head, node_t *node);

#endif
