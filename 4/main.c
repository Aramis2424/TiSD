#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "errors.h"
#include "functions.h"
#include "stack_arr.h"
#include "stack_list.h"
#include "analise.h"

#define MAX_MENU 7
#define MIN_MENU 0

int main(void)
{
    char stack_arr[COUNT_WORD][LEN_WORD + 1];
    int arr_len = -1;

    stack_list_t head;
    head.name[0] = '\0';
    head.next = NULL;

    stack_list_t* arr_free_mem[COUNT_WORD];
    int len_arr_free_mem = 0;

    intro_void();
    int choice = -1;
    char str[15];
    while (choice != 0)
    {
        menu_print();
        if (scanf("%s", str) != 1 || is_num(str) == FALSE)
        {
            printf("Invalid menu code\n");
            printf("Please try again\n\n");
            continue;
        }
        choice = atoi(str);
        if (choice > MAX_MENU || choice < MIN_MENU)
        {
            printf("Invalid menu code\n");
            printf("Please try again\n\n");
            continue;
        }
        if (choice == 0)
        {
            printf("End program!\n");
            break;
        }

        if (choice == 1)
        {
            if (arr_len >= COUNT_WORD - 1)
            {
                printf("Sorry, but stack overflow.\n");
                printf("You cannot add new word.\n\n");
                continue;
            }
            char str[LEN_WORD + 3];
            printf("Input word: ");
            setbuf(stdin, 0);
            if (fgets(str, LEN_WORD+2, stdin)==NULL||strlen(str)==LEN_WORD+2)
            {
                fflush(stdin);
                setbuf(stdin, 0);
                printf("Sorry, but input wrang.\n");
                printf("Please, try again.\n\n");
                continue;
            }
            stack_arr_push(stack_arr, &arr_len, str);
            stack_list_push(&head, str, arr_free_mem, &len_arr_free_mem);
            printf("Add is done!\n\n");
            continue;
        }
        if (choice == 2)
        {
            if (stack_arr_print(stack_arr, &arr_len) != TRUE)
            {
                printf("Sorry, but stack is empty.\n");
                printf("There are not words to print.\n\n");
                continue;
            }
            stack_list_print(&head);
            printf("\n");
            continue;
        }
        if (choice == 3)
        {
            if (stack_arr_print_rev(stack_arr, &arr_len) != TRUE)
            {
                printf("Sorry, but stack is empty.\n");
                printf("There are not words to print.\n\n");
                continue;
            }
            stack_list_print_rev(&head);
            printf("\n");
            continue;
        }
        if (choice == 4)
        {
            if (stack_arr_pop(&arr_len) != TRUE)
            {
                printf("Sorry, but stack is empty.\n");
                printf("You cannot del word.\n\n");
                continue;
            }
            stack_list_pop(&head, arr_free_mem, &len_arr_free_mem);
            printf("Del is done!\n\n");
            continue;
        }
        if (choice == 5)
        {
            stack_list_print_free_mem(arr_free_mem, &len_arr_free_mem);
            continue;
        }
        if (choice == 6)
        {
            if (stack_arr_clear(&arr_len) != TRUE)
            {
                printf("Sorry, but stack is already empty.\n\n");
                continue;
            }
            stack_list_clear(&head, arr_free_mem, &len_arr_free_mem);
            printf("Clear is done!\n\n");
            continue;
        }
        if (choice == 7)
        {
            analise(stack_arr, &arr_len, &head);
            continue;
        }
    }
    stack_arr_clear(&arr_len);
    stack_list_clear(&head, arr_free_mem, &len_arr_free_mem);
    return EXIT_SUCCESS;
}
