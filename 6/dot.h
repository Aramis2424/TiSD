#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include "tree.h"

void apply_pre(tree_node *head, void (*f)(tree_node *, void *), void *arg);
void todot(tree_node *head, void *p);
void exporttodot(FILE *f, tree_node *head);

#endif //DOT_H
