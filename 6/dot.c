#include <stdlib.h>
#include "dot.h"

void apply_pre(tree_node *head, void (*f)(tree_node *, void *), void *arg)
{
    if (head == NULL)
        return;

    f(head, arg);
    apply_pre(head->right, f, arg);
    apply_pre(head->left, f, arg);
}

void todot(tree_node *head, void *p)
{
    FILE *f = p;

    if (head->left)
        fprintf(f, "%d -> %d;\n", head->number, head->left->number);
    else
        fprintf(f, "%d -> A [ style = invis ];\n", head->number);

    if (head->right)
        fprintf(f, "%d -> %d;\n", head->number, head->right->number);
    else
        fprintf(f, "%d -> A [ style = invis ];\n", head->number);
}

void exporttodot(FILE *f, tree_node *head)
{
    fprintf(f, "digraph tree {\n");
    fprintf(f, "A [ label = \"A\", style = invis ];\n");

    apply_pre(head, todot, f);
    fprintf(f, "}\n");
}
