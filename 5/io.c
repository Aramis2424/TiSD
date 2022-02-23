

#include "io.h"

void print_hello()
{
    printf("\nMenu:\n"
           "1 - queque -- array.\n"
           "2 - queque -- list.\n"
           "3 - change times.\n"
           "4 - compartions.\n"
           "0 - Exit.\n"
           );
}

void printf_input()
{
    printf("\nChoice is: ");
}

void clean_my()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int check_float(double *const number)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (double)atof(num);


    return OK;
}

int check_number(int *const number, const int l, const int r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (*number < l || *number > r)
    {
        return INV_NUM_CHOICE;
    }

    return OK;
}

void len_swow(queue_t *queue)
{
    //printf("Current length %s: \t %d\n", queue->name, queue->tmp_len);
    printf("Now len %s: \t %d\n", queue->name, queue->tmp_len);
    if (queue->count_req > 0)
    {

        printf("AVG len %s: \t %lf\n", queue->name,
                (double)queue->sum_len / (double)queue->count_req);
    }
}
