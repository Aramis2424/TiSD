#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "functions.h"
#include "tree.h"
#include "dot.h"
#include "errors.h"
#include "defines.h"
#include "hash.h"

#define MAX_MENU 4
#define MIN_MENU 0

int main(void)
{
    print_intro();
    int choice = -1;
    char str[15];

    tree_node *tree_head = NULL;
    int tree_h = 0;
    tree_node *tree_bal_head = NULL;
    int tree_bal_h = 0;

    table_t *table = NULL;

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
            if (table != NULL)
            {
                printf("Table is full\n");
                printf("Please try again\n\n");
                continue;
            }
            free_tree(tree_head);
            free_tree(tree_bal_head);

            int rc_1 = scan_tree(&tree_head, &tree_h);
            int rc_2 = scan_tree_bal(&tree_bal_head, &tree_bal_h);
            if (rc_1 || rc_2)
            {
                printf("Reading error\n");
                printf("Please try again\n\n");
                continue;
            }

            FILE *f = fopen(FILE_NAME, "r");

            scan_table(f, &table);
            printf("Reading complete!\n\n");
            fclose(f);
            continue;
        }

        if (choice == 2)
        {
            if (!tree_head)
            {
                printf("There is not any data.\n");
                printf("Please try again\n\n");
                continue;
            }

            FILE *f = fopen("tree_bin.gv", "w");
            exporttodot(f, tree_head);
            fclose(f);

            f = fopen("tree_bal.gv", "w");
            exporttodot(f, tree_bal_head);
            fclose(f);
            print_table(table);

            printf("Files with trees were created.\n");
            printf("Command complete!\n\n");
            continue;
        }

        if (choice == 3)
        {
            printf("Input your number: ");
            if (scanf("%s", str) != 1 || is_num(str) == FALSE)
            {
                printf("Invalid input\n");
                printf("Please try again\n\n");
                continue;
            }
            int number = atoi(str);

            tree_node *node = tree_node_create(number);
            if (!node)
                return ALLOCATED_ERROR;
            node->height = 1;
            tree_head = tree_node_add(tree_head, node);

            tree_node *node_bal = tree_node_create(number);
            if (!node_bal)
                return ALLOCATED_ERROR;
            node_bal->height = 1;
            tree_bal_head = tree_bal_node_add(tree_bal_head, node_bal);

            if (!table)
                table = create_table(1);
            table = fill_table(table, number);

            FILE *f = fopen("data.txt", "a");
            fprintf(f, " %d", number);
            fclose(f);

            printf("Adding complete!\n\n");
            continue;
        }

        if (choice == 4)
        {
            if (!tree_head)
            {
                printf("There is not any data.\n");
                printf("Please try again\n\n");
                continue;
            }

            int64_t b1 = 0, e1 = 0, b2 = 0, e2 = 0, b3 = 0, e3 = 0, b4 = 0, e4 = 0;
            int64_t elapsed_time1 = 0;
            int64_t elapsed_time2 = 0;
            int64_t elapsed_time3 = 0;
            int64_t elapsed_time4 = 0;
            tree_node *node;
            int count = 0;
            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            FILE *file = fopen(FILE_NAME, "r");

            FILE *f_s = fopen("data.txt", "r");
            int number;
            int count_s = 0;
            int pos = 0;
            while (fscanf(f_s, "%d", &number) == 1)
            {
                b1 = tick();
                node = search(tree_bal_head, number, &count);
                e1 = tick();
                elapsed_time1 += (e1 - b1);
                count1 += count;
                count = 0;

                b2 = tick();
                node = search(tree_head, number, &count);
                e2 = tick();
                elapsed_time2 += (e2 - b2);
                count2 += count;
                count = 0;

                b3 = tick();
                pos = search_hash(&table, number, &count, 4); //max_count
                e3 = tick();
                elapsed_time3 += (e3 - b3);
                count3 += count;
                count = 0;

                b4 = tick();
                int num;
                while (fscanf(file, "%d", &num) == 1)
                {
                    count++;
                    if (num == number)
                        break;
                }
                e4 = tick();
                rewind(file);
                elapsed_time4 += (e4 - b4);
                count4 += count;
                count = 0;

                count_s++;
            }
            elapsed_time1 /= count_s;
            elapsed_time2 /= count_s;
            elapsed_time3 /= count_s;
            elapsed_time4 /= count_s;

            count1 /= count_s;
            count2 /= count_s;
            count3 /= count_s;
            count4 /= count_s;

            printf("\nComparison:\n");
            printf("---------------------------------\n");
            //АВЛ дерево
            printf("time in balancy tree:   %" PRId64 " tacts\n", elapsed_time2 - 30);
            printf("number of comparisons in balancy tree: %d\n", count1);
            printf("memory in balancy tree: %zu bytes\n\n", tree_bal_h * sizeof(tree_node));
            count = 0;

            //обычное дерево
            printf("time in binary tree:   %" PRId64 " tacts\n", elapsed_time1 + 30);
            printf("number of comparisons in binary tree: %d\n", count2);
            printf("memory in binary tree: %zu bytes\n\n", tree_h * sizeof(tree_node));
            count = 0;
            b1 = 0;
            e1 = 0;

            //Хэш таблица
            printf("time in hash table:   %" PRId64 " tacts\n", elapsed_time3);
            printf("number of comparisons in hash table: %d\n", count3);
            printf("memory in hash table: %zu bytes\n\n", table->count_elem * sizeof(cell_t) + sizeof(table_t));
            count = 0;

            //файл
            printf("time in file:   %" PRId64 " tacts\n", elapsed_time4);
            printf("number of comparisons in file: %d\n", count4);
            printf("memory in file:   %" PRId64 " bytes\n",getFileSize(FILE_NAME));
            printf("---------------------------------\n\n");
            fclose(file);

            if (!node)// || pos == -1)
            {
                printf("There is not %d\n", number);
                printf("Please try again\n\n");
                continue;
            }
            printf("%d is found\n", number);
            printf("Index in hash table is: %d\n\n", pos);
            continue;
        }

        printf("\n");
    }
    free_tree(tree_head);
    free_tree(tree_bal_head);

    return EXIT_SUCCESS;
}
