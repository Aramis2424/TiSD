#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <sys/time.h>
#include "errors.h"
#include "structures.h"
#include "read_file.h"
#include "print.h"
#include "functions.h"
#include "del_student.h"
#include "sort.h"       //ПАМЯТЬ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "compare.h"

#define MAX_MENU 9
#define MIN_MENU 0

int main(void)
{
    students_t arr[ARR_SIZE];
    keys_t arrk[ARR_SIZE];
    table_t table;
    int len = 0;
    int rc;
    print_menu();
    int choice = -1;
    char str[5];
    while (choice != 0)
    {
        if (scanf("%s", str) != 1)
        {
            printf("Invalid menu code\n");
            printf("Please try again\n");
            continue;
        }
        choice = atoi(str);
        if (choice > MAX_MENU || choice < MIN_MENU)
        {
            printf("Invalid menu code\n");
            printf("Please try again\n");
            continue;
        }
        if (choice == 0)
        {
            printf("End program");
            break;
        }

        if (choice == 1)
        {
            rc = read_file(&table, arr, &len, arrk);
            if (len == 0)
            {
                printf("Sorry, but the file is empty\n");
                return EMPTY_FILE;
            }
            if (rc == TOO_BIG_DATA)
            {
                printf("too big data");
                return EXIT_FAILURE;
            }
            if (rc != TRUE)
            {
                printf("Something go wrang, new command: \n");
                continue;
            }
            printf("Command complete!\n");
        }
        if (choice == 2)
        {
            rc = add_student(&table, arr, &len, arrk);
            if (rc != TRUE)
            {
                printf("New command: \n");
                continue;
            }
            printf("Command complete!\n");
        }

        if (choice == 3)
        {
            if (is_empty(&len))
                continue;
            double score;
            printf("Input the the score (maybe float or integer, but positive,"
                    " not greater then 5.0): ");
            if (scanf("%lf", &score) != 1 || score < 0)
            {
                score *= 10;
                score = round(score);
                score /= 10;
                printf("Invalid score\n");
                printf("New command: \n");
                continue;
            }
            del_student(arr, &len, arrk, score);
            printf("Command complete!\n");
        }

        if (choice == 4)
        {
            if (is_empty(&len))
                continue;
            sort_key_bubble(arrk, len);
            print_keys(arrk, &len);
            printf("Command complete!\n");
        }
        if (choice == 5)
        {
            if (is_empty(&len))
                continue;
            sort_q(arr, len);
            print_all(arr, &len);
            printf("Command complete!\n");
        }
        if (choice == 6)
        {
            if (is_empty(&len))
                continue;
            sort_key_bubble(arrk, len);
            print_all_k(arr, &len, arrk);
            printf("Command complete!\n");
        }
        if (choice == 7)
        {
            if (is_empty(&len))
                continue;
            print_all(arr, &len);
            printf("Command complete!\n");
        }
        if (choice == 8)
        {
            if (is_empty(&len))
                continue;
            printf("Print the year of entering (year is positive integer): ");
            int year;
            if (scanf("%d", &year) == 1 && year > 0)
                print_part(arr, &len, &year);
            else
            {
                printf("Invalid year\n");
                printf("New command: \n");
                continue;
            }
            printf("Command complete!\n");
        }
        if (choice == 9)
        {
            students_t narr[ARR_SIZE];
            keys_t narrk[ARR_SIZE];
            table_t ntable;
            int nlen = 0;

            rc = compare(&ntable, narr, &nlen, narrk);
            if (rc == TOO_BIG_DATA)
                return rc;

            printf("Command complete!\n");
        }
        printf("\n\nWhat's next?\n");
        print_menu();
    }
    return EXIT_SUCCESS;
}
