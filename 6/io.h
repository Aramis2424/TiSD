#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "tree.h"
#include "hash.h"

void print_intro(void);
void print_menu(void);
int scan_tree(tree_node **head, int *count);
int scan_tree_bal(tree_node **head, int *count);
void scan_table(FILE *f, table_t **table);
void print_table(table_t *table);

#endif
