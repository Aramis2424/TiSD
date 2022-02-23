#include <stdio.h>
#include <string.h>
#include "stack_arr.h"
#include "errors.h"

int stack_arr_push(char arr[][LEN_WORD + 1], int *len, char str[])
{
    (*len)++;
    strncpy(arr[*len], str, LEN_WORD);
    return TRUE;
}

int stack_arr_print(char arr[][LEN_WORD + 1], int *len)
{
    if (*len == -1)
        return EMPTY_STACK;
    printf("Stack (arr):\n");
    for (int i = 0; i < *len + 1; i++)
        printf("   %s", arr[i]);
    return TRUE;
}

int stack_arr_print_rev(char arr[][LEN_WORD + 1], int *len)
{
    if (*len == -1)
        return EMPTY_STACK;
    printf("Stack (arr):\n");
    for (int i = *len; i > -1; i--)
    {
        int k;
        for (k = 0; arr[i][k] != '\0'; k++);
        printf("   ");
        for (int j = k - 1; j > -1; j--)
            if (arr[i][j] != '\n')
                printf("%c", arr[i][j]);
        printf("\n");
    }
    return TRUE;
}

int stack_arr_pop(int *len)
{
    if (*len == -1)
        return EMPTY_STACK;
    (*len)--;
    return TRUE;
}

int stack_arr_clear(int *len)
{
    if (*len == -1)
        return EMPTY_STACK;
    *len = -1;
    return TRUE;
}
