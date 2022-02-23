#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "functions.h"
#include "dot.h"
#include "errors.h"
#include "defines.h"
#include "processing.h"

#define MAX_MENU 4
#define MIN_MENU 0

int main(void)
{
    print_intro();
    int choice = -1;
    char str[15];
    int matrix[MAX_N][MAX_N];
    node_t arrb[MAX_N];
    int lenb = 0;

    int way[MAX_N];
    int lenw = 0;

    //node_t arrw[MAX_N];
    //int lenw = 0;

    while (choice != 0)
    {
        print_menu();
        printf("Your choice is: ");

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
            lenw = 0;
            scan_graph(FILE_NAME, matrix, arrb, &lenb);
            printf("Command complete\n\n");

            continue;
        }

        if (choice == 2)
        {
            if (lenb == 0)
            {
                printf("Graph is empty!\n");
                printf("Please try again\n\n");
                continue;
            }
            FILE *f_out = fopen(GRAPH, "w");
            print_graph(f_out, matrix, MAX_N, way, lenw);
            fclose(f_out);
            system("dot.exe -Tpng graph.dot -o picture.png");
            system("picture.png");
            printf("Command complete\n\n");
            continue;
        }

        if (choice == 3)
        {
            if (lenb == 0)
            {
                printf("Graph is empty!\n");
                printf("Please try again\n\n");
                continue;
            }
            print_stdout_graph(arrb, lenb);
            printf("\nCommand complete\n\n");
            continue;
        }

        if (choice == 4)
        {
            if (lenb == 0)
            {
                printf("Graph is empty!\n");
                printf("Please try again\n\n");
                continue;
            }
            //int rc = find_longest_way(arrb, lenb, arrw, lenw);
            max_way(matrix, MAX_N, way, &lenw);
            printf("The longest way:\n ");
            for (int i = 0; i < lenw; i++)
            {
                printf("%d", way[i]);
                if (i < lenw - 1)
                    printf(" -> ");
            }
            printf("\n");
            printf("\nCommand complete\n\n");
            continue;
        }

    }

    return EXIT_SUCCESS;
}







//for (int i = 0; i < MAX_N; i++)
//{
//    for (int j = 0; j < MAX_N; j++)
//        printf("%d ", matrix[i][j]);
//    printf("\n");
//}
