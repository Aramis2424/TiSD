#ifndef TREE_H
#define TREE_H

typedef struct tree_node tree_node;
struct tree_node
{
    int number;
    int height;

    tree_node *left;
    tree_node *right;
};

tree_node *tree_node_create(int number);
tree_node *tree_node_add(tree_node *head, tree_node *node);
tree_node *tree_bal_node_add(tree_node *head, tree_node *node);
tree_node *balance_tree(tree_node *head);
tree_node *search(tree_node *head, int key, int *count);
void free_tree(tree_node *head);

#endif //TREE_H
