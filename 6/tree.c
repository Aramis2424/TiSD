#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

tree_node *tree_node_create(int number)
{
    tree_node *node = malloc(sizeof(tree_node));

    if (node)
    {
        node->number = number;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

tree_node *tree_node_add(tree_node *head, tree_node *node)
{
    if (!head)
        return node;
    else
    {
        if (node->number < head->number)
            head->left = tree_node_add(head->left, node);
        else if (node->number > head->number)
            head->right = tree_node_add(head->right, node);
        else
            free(node);
    }

    return head;
}

tree_node *tree_bal_node_add(tree_node *head, tree_node *node)
{
    if (!head)
        return node;

    if (node->number > head->number)
        head->right = tree_bal_node_add(head->right, node);
    else if (node->number < head->number)
        head->left = tree_bal_node_add(head->left, node);
    else
        free(node);

    return balance_tree(head);
}

int own_height(tree_node *head)
{
    return head ? head->height : 0;
}

void new_height(tree_node *head)
{
    int hl = own_height(head->left);
    int hr = own_height(head->right);
    head->height = ((hl > hr) ? hl : hr) + 1;
}

int factorlr(tree_node *head)
{
    return own_height(head->right) - own_height(head->left);
}

tree_node *rotate_right(tree_node *head)
{
    tree_node *tmp = head->left;
    head->left = tmp->right;
    tmp->right = head;
    new_height(head);
    new_height(tmp);

    return tmp;
}

tree_node *rotate_left(tree_node *head)
{
    tree_node *tmp = head->right;
    head->right = tmp->left;
    tmp->left = head;
    new_height(head);
    new_height(tmp);

    return tmp;
}

tree_node *balance_tree(tree_node *head)
{
    new_height(head);
    if (factorlr(head) == 2)
    {
        if (factorlr(head->right) < 0)
            head->right = rotate_right(head->right);
        return rotate_left(head);
    }

    if (factorlr(head) == -2)
    {
        if (factorlr(head->left) > 0)
            head->left = rotate_left(head->left);
        return rotate_right(head);
    }

    return head;
}

tree_node *search(tree_node *head, int key, int *count)
{
    tree_node *node = NULL;
    if (head != NULL)
    {
        (*count)++;
        if (key == head->number)
            return head;
        else if (key < head->number)
            node = search(head->left, key, count);
        else if (key > head->number)
            node = search(head->right, key, count);
    }
    return node;
}

void apply_po(tree_node *head, void (*f)(tree_node *), void *arg)
{
    if (head == NULL)
        return;

    apply_po(head->right, f, arg);
    apply_po(head->left, f, arg);
    f(head);
}

void free_tree_node(tree_node *head)
{
    if (head)
        free(head);
    head = NULL;
}

void free_tree(tree_node *head)
{
    if (head)
        apply_po(head, free_tree_node, NULL);
}
