#ifndef LIST_H
#define LIST_H

#include "structures.h"
#include "timemem.h"
#include "io.h"

node_t* create_elem(char c);
node_t* pushfront(node_t *head, node_t *elem);
node_t* popfront(node_t **head);
node_t* popend(node_t **head);
void freeall(node_t *head);

void sim_list(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4, int flag);
node_t *queuelist_push(node_t *queue, char c, node_t **user_memory,
                    int *user_count, node_t **free_memory,
                    int *free_count, int *second_use);
node_t *queue_list_pop(node_t **queue);

#endif // LIST_H
