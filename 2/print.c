#include <stdio.h>
#include "print.h"

void print_menu()
{
    printf("Menu:\n");
    printf("  1)Read information from the file;\n");
    printf("  2)Add student to the table;\n");
    printf("  3)Delete students, who have score less then ...;\n");
    printf("  4)Sort keys by student`s age (without sorting table);\n");
    printf("  5)Sort table by student`s age;\n");
    printf("  6)Sort table by sorting keys;\n");
    printf("  7)Print all students\n");
    printf("  8)Print students from dormitory, entered in ...;\n");
    printf("  9)Compare different sorts;\n");
    printf("  0)Exit.\n");
    printf("Your choice is: ");
}

void print_all(students_t const arr[], int *len)
{
    for (int i = 0; i < (*len); i++)
    {
        printf("%d)", i + 1);
        printf("%s ", arr[i].surname);
        printf("%s, ", arr[i].name);
        printf("Group: %d, ", arr[i].group);
        if (arr[i].gender == 1)
            printf("%c, ", 'M');
        else
            printf("%c, ", 'W');
        printf("Age: %d, ", arr[i].age);
        printf("Score: %.1lf, ", arr[i].avg_score);
        printf("Year: %d, ", arr[i].year);
        if (arr[i].type == 1)
        {
            printf("Live in flat: ");
            printf("%s, ", arr[i].type_housing.flat.street);
            printf("%d, ", arr[i].type_housing.flat.house);
            printf("f. %d;", arr[i].type_housing.flat.room);
        }
        else
        {
            printf("Live in dormitory ");
            printf("%d, ", arr[i].type_housing.dormitory.dormitory);
            printf("room %d;", arr[i].type_housing.dormitory.room);
        }
        printf("\n");
    }
}

void print_part(students_t const arr[], int *len, int *year)
{
    int j = 1;
    for (int i = 0; i < *len; i++)
    {
        if (arr[i].year == *year)
            if (arr[i].type == 0)
            {
                printf("%d)", j);
                printf("%s ", arr[i].surname);
                printf("%s, ", arr[i].name);
                printf("Group: %d, ", arr[i].group);
                if (arr[i].gender == 1)
                    printf("%c, ", 'M');
                else
                    printf("%c, ", 'W');
                printf("Age: %d, ", arr[i].age);
                printf("Score: %.2lf, ", arr[i].avg_score);
                printf("Year: %d, ", *year);
                printf("Live in dormitory ");
                printf("%d, ", arr[i].type_housing.dormitory.dormitory);
                printf("room %d;", arr[i].type_housing.dormitory.room);
                printf("\n");
                j++;
            }
    }
    if (j == 1)
        printf("No such students, who entered in %d\n", *year);
}

void print_all_k(students_t const arr[], int *len, keys_t arrk[])
{
    int j = 1;
    for (int n = 0; n < *len; n++)
    {
        int i = arrk[n].id;
        printf("%d)", j);
        printf("%s ", arr[i].surname);
        printf("%s, ", arr[i].name);
        printf("Group: %d, ", arr[i].group);
        if (arr[i].gender == 1)
            printf("%c, ", 'M');
        else
            printf("%c, ", 'W');
        printf("Age: %d, ", arr[i].age);
        printf("Score: %.2lf, ", arr[i].avg_score);
        printf("Year: %d, ", arr[i].year);
        printf("Live in dormitory ");
        printf("%d, ", arr[i].type_housing.dormitory.dormitory);
        printf("room %d;", arr[i].type_housing.dormitory.room);
        printf("\n");
        j++;
    }
}

void print_keys(keys_t arrk[], int *len)
{
    for (int i = 0; i < *len; i++)
    {
        printf("%d)", i + 1);
        printf("id: %d, ", arrk[i].id);
        printf("age: %d, ", arrk[i].age);
        printf("\n");
    }
}
