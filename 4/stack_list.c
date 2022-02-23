#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack_list.h"

stack_list_t* list_create(const char *word)
{
    stack_list_t *new = malloc(sizeof(stack_list_t));
    if (new)
    {
        strncpy(new->name, word, LEN_WORD);
        new->next = NULL;
    }
    return new;
}

void list_free(stack_list_t *elem)
{
    free(elem);
}

stack_list_t* list_add_end(stack_list_t *head, stack_list_t *new)
{
    stack_list_t *cur = head;
    if (!head)
        return new;
    for (; cur->next; cur = cur->next);
    cur->next = new;
    return head;
}

int stack_list_push(stack_list_t *head, char *str, stack_list_t* arr_free_mem[], int *len_arr_free_mem)
{
    stack_list_t *tmp = list_create(str);
    list_add_end(head, tmp);
    for (int i = 0; i < *len_arr_free_mem; i++)
        if (arr_free_mem[i] == tmp)
        {
            for (int j = i; j < *len_arr_free_mem - 1; j++)
                arr_free_mem[j] = arr_free_mem[j + 1];
            (*len_arr_free_mem)--;
            break;
        }
    return TRUE;
}

int stack_list_print(stack_list_t *head)
{
    stack_list_t *cur = head;
    printf("Stack list:\n");
    while (cur->next)
    {
        cur = cur->next;
        printf("   %p ", cur);
        printf("%s", cur->name);
    }
    printf("*size of one structure: %0x\n", (int)sizeof(*head));
    return TRUE;
}

int stack_list_print_rev(stack_list_t *head)
{
    stack_list_t *cur = head;
    int n, m;
    for (n = 0; cur->next; cur = cur->next, n++);
    m = n;

    printf("Stack list:\n");
    cur = head;
    for (int a = 0; a < n; a++)
    {
        int i;
        for (i = 0; i < m; i++, cur = cur->next);
        m--;
        for (i = 0; cur->name[i] != '\0'; i++);
        printf("   ");
        for (int j = i - 1; j > -1; j--)
            if (cur->name[j] != '\n')
                printf("%c", cur->name[j]);
        printf("\n");
        cur = head;
    }

    return TRUE;
}

int stack_list_pop(stack_list_t *head, stack_list_t* arr_free_mem[], int *len)
{
    stack_list_t *cur = head;
    stack_list_t *tmp;
    for (; cur->next; tmp = cur, cur = cur->next);
    tmp->next = NULL;

    int flag = 0;
    for (int i = 0; i < *len; i++)
        if (arr_free_mem[i] == cur)
            flag = 1;
    if (!flag)
    {
        arr_free_mem[*len] = cur;
        (*len)++;
    }

    list_free(cur);

    return TRUE;
}

void stack_list_clear(stack_list_t *head, stack_list_t *arr_free_mem[], int *len)
{
    stack_list_t *next = head;
    head = head->next;
    next->next = NULL;
    int flag;
    for (; head; head = next)
    {
        flag = 0;
        next = head->next;
        for (int i = 0; i < *len; i++)
            if (arr_free_mem[i] == head)
                flag = 1;
        if (!flag)
        {
            arr_free_mem[*len] = head;
            (*len)++;
        }
        list_free(head);
    }
}

int stack_list_print_free_mem(stack_list_t *arr_free_mem[], int *len)
{
    if (*len == 0)
    {
        printf("There is no freed memory\n\n");
        return TRUE;
    }
    printf("Free memory addresses:\n");
    for (int i = 0; i < *len; i++)
    {
        printf("  %d)%p\n", i + 1, arr_free_mem[i]);
    }
    printf("\n");
    return TRUE;
}
