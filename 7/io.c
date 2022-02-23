#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "defines.h"
#include "errors.h"
#include "functions.h"

void print_intro(void)
{
    printf("Hello!\n");
    printf("This program \n");
    printf("------------------------------------------\n");
    printf("\n");
}

void print_menu(void)
{
    printf("Menu:\n");
    printf("   1)Read graph from file;\n");
    printf("   2)Print graph in graph form;\n");
    printf("   3)Print graph in text form;\n");
    printf("   4)Find the longest way;\n");
    printf("   0)Exit;\n");
    printf("----------\n");
}

int scan_graph(char *str, int matrix[][MAX_N], node_t arrb[], int *len)
{
    FILE *f_in = fopen(str, "r");
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            matrix[i][j] = 0;
    int n, m;
    int flag = 0;
    node_t *cur = NULL;

    while (fscanf(f_in, "%d %d", &n, &m) == 2) //создаем список здесь
    {
        matrix[n][m] = 1;
        for (int q = 0; q < *len; q++)
        {
            if (arrb[q].num == n)
            {
                flag = 1;
                cur = &arrb[q];
                while (cur->next != NULL)
                {
                    cur = cur->next;
                }
                node_t *tmp = calloc(1, sizeof(node_t));
                tmp->next = NULL;
                tmp->num = m;

                cur->next = tmp;
                break;
            }
        }

        if (flag == 0)
        {
            arrb[*len].next = NULL;
            arrb[*len].num = n;

            node_t *tmp = calloc(1, sizeof(node_t));
            tmp->next = NULL;
            tmp->num = m;

            arrb[*len].next = tmp;

            (*len)++;
        }
        flag = 0;
    }
    fclose(f_in);

    return TRUE;
}

void print_stdout_graph(node_t arrb[], int len)
{
    for (int i = 0; i < len; i++)
    {
        node_t *cur = &arrb[i];
        while (cur)
        {
            printf("%d ->", cur->num);
            cur = cur->next;
        }
        printf("\n");
    }
}

struct stop_index
{
    int i;
    int j;
};

int is_stop_index(int i, int j, struct stop_index arr[], int len)
{
    for (int n = 0; n <= len; n++)
        if (i == arr[n].i && j == arr[n].j)
            return 1;
    return 0;
}

void print_graph(FILE *stream, int matr[][MAX_N], int n, int path[], int path_len)
{
    fprintf(stream, "digraph { \n\trankdir=LR; \n");

    struct stop_index *stop_arr = calloc(n*n, sizeof (struct stop_index));
    int stop_len = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matr[i][j] == 1)
            {
                if (is_stop_index(i, j, stop_arr, stop_len) != 0)
                    continue;
                if (matr[j][i] == 1 && i != j)
                {
                    fprintf(stream, "\t%d -> %d[dir=both, penwidth=1.0];\n", i, j);
                    stop_len++;
                    stop_arr[stop_len].i = j;
                    stop_arr[stop_len].j = i;
                }
                else
                    fprintf(stream, "\t%d -> %d[penwidth=1.0];\n", i, j);
            }

    for (int i = 0; i<path_len-1; i++)
        fprintf(stream, "\t%d -> %d[color=red, penwidth=1.5];\n", path[i], path[i+1]);

    free(stop_arr);
    fprintf(stream, "}\n");
}
