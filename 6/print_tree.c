void print_tree(tree_node *head, int down, int arrow)
{
    if (head)
    {
        print_tree(head->right, down + 1, 2);
        for (int i = 0; i < down; i++)
        {
            printf("       ");
        }
        if (arrow == 1)
        {
            printf(" \\ ");
        }
        else if (arrow == 2)
        {
            printf(" / ");
        }
        else if (arrow == 0)
        {
            printf("   ");
        }

        printf(" %d\n", head->number);

        print_tree(head->left, down + 1, 1);
    }
}

print_tree(tree_head, 0, 0);