#ifndef PROVESSING_H
#define PROVESSING_H

#include "defines.h"
#include "errors.h"

typedef struct node_t node_t;
struct node_t
{
    int num;
    node_t *next;
};

int find_longest_way(node_t arrb[], int lenb, node_t arrw[], int lenw);
int mаx_wаy(node_t gra[], int n, int way[], int *lenw);

int max_way(int matr[][MAX_N], int n, int max_path[], int *max_len);

#endif
