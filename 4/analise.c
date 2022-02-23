#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "functions.h"
#include "analise.h"

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void analise(char stack_arr[][LEN_WORD + 1], int *arr_len, stack_list_t *head)
{
    printf("Input count of words (maximum is %d): ", COUNT_WORD);
    int n;

    char str[15];
    if (scanf("%s", str) != 1 || is_num(str) == FALSE)
    {
        printf("Input error, plese try again.\n\n");
        return;
    }
    n = atoi(str);
    if (n > COUNT_WORD)
    {
        printf("Number is bigger then %d, plese try again.\n\n", COUNT_WORD);
        return;
    }
    if (n < 1)
    {
        printf("Number should be integer, plese try again.\n\n");
        return;
    }

    head->name[0] = '\0';
    head->next = NULL;

    stack_list_t* arr_free_mem[COUNT_WORD];
    int len_arr_free_mem = 0;

    stack_arr_clear(arr_len);
    stack_list_clear(head, arr_free_mem, &len_arr_free_mem);

    int64_t b1, e1, b2, e2;
    int64_t elapsed_time = 0;

    FILE *f = fopen("data.txt", "r");
    printf("\nCompare:\n");
    int a = 1;
    for (int i = 0; i < n; i++)
    {
        char str[LEN_WORD - 1];
        setbuf(stdin, 0);
        fgets(str, LEN_WORD - 1, f);

        b1 = tick();
        stack_arr_push(stack_arr, arr_len, str);
        e1 = tick();
        elapsed_time += (e1 - b1);

        str[0] = '\0';
        a++;
        if (a >= 10)
        {
            a = 1;
            rewind(f);
        }
    }
    printf(" *Push:\n");
    printf("   >Array:\n");
    printf("     -time:   %" PRId64 " tacts\n", elapsed_time);
    printf("     -memory: %lld bytes\n", COUNT_WORD * sizeof(stack_arr[0]));

    elapsed_time = 0;
    a = 1;
    rewind(f);
    for (int i = 0; i < n; i++)
    {
        char str[LEN_WORD - 1];
        setbuf(stdin, 0);
        fgets(str, LEN_WORD - 1, f);

        b2 = tick();
        stack_list_push(head, str, arr_free_mem, &len_arr_free_mem);
        e2 = tick();
        elapsed_time += (e2 - b2);
        str[0] = '\0';
        a++;
        if (a >= 10)
        {
            a = 1;
            rewind(f);
        }
    }
    printf("   >List:\n");
    printf("     -time:   %" PRId64 " tacts\n", elapsed_time);
    printf("     -memory: %lld bytes\n", n * sizeof(*head));

    elapsed_time = 0;
    b1 = tick();
    stack_arr_pop(arr_len);
    e1 = tick();
    elapsed_time += (e1 - b1);

    printf(" *Pop:\n");
    printf("   >Array:\n");
    printf("     -time:   %" PRId64 " tacts\n", elapsed_time);
    printf("     -memory: %lld bytes\n", COUNT_WORD * sizeof(stack_arr[0]));

    elapsed_time = 0;
    b2 = tick();
    stack_list_pop(head, arr_free_mem, &len_arr_free_mem);
    e2 = tick();
    elapsed_time += (e2 - b2);

    printf("   >List:\n");
    printf("     -time:   %" PRId64 " tacts\n", elapsed_time);
    printf("     -memory: %lld bytes\n", (n - 1) * sizeof(*head));
    fclose(f);
}
