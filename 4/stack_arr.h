#ifndef STACK_ARR_H
#define STACK_ARR_H

#include "errors.h"

int stack_arr_push(char arr[][LEN_WORD + 1], int *len, char str[]);
int stack_arr_print(char arr[][LEN_WORD + 1], int *len);
int stack_arr_print_rev(char arr[][LEN_WORD + 1], int *len);
int stack_arr_pop(int *len);
int stack_arr_clear(int *len);

#endif
