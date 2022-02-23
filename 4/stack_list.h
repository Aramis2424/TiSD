#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "errors.h"

typedef struct stack_list_t stack_list_t;
struct stack_list_t
{
    char name[LEN_WORD + 1];
    stack_list_t *next;
};

stack_list_t* list_create(const char *word);
void list_free(stack_list_t *elem);
stack_list_t* list_add_end(stack_list_t *head, stack_list_t *word);

int stack_list_push(stack_list_t *head, char *str, stack_list_t *arr_free_mem[], int *len_arr_free_mem);
int stack_list_print(stack_list_t *head);
int stack_list_print_rev(stack_list_t *head);
int stack_list_pop(stack_list_t *head, stack_list_t *arr_free_mem[], int *len);
void stack_list_clear(stack_list_t *head, stack_list_t *arr_free_mem[], int *len);
int stack_list_print_free_mem(stack_list_t *arr_free_mem[], int *len);

#endif
