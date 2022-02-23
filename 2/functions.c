#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "structures.h"

int is_double(char str[])
{
    int flag = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]) && str[i])
        {
            if (!flag && str[i] == '.')
                flag = 1;
            else
                return FALSE;
        }
    return TRUE;
}

int is_integer(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return  FALSE;;
    return TRUE;
}

int is_empty(int *len)
{
    if (*len != 0)
        return FALSE;
    printf("Sorru, but the file is empty\n");
    printf("Please, at first make the 1st or 2nd command\n");
    return TRUE;
}

void del_snl(char str[])
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

int add_student(table_t *table, students_t arr[], int *len, keys_t arrk[])
{
    if (*len >= ARR_SIZE)
    {
        printf("Sorry, but the array is full\n");
        return FALSE;
    }
    char str[WORD_LEN];
    getchar();

    printf("Input student`s surname (without spaces): ");
    if (fgets(str, WORD_LEN, stdin) && !strstr(str, " "))
    {
        del_snl(str);
        strncpy(table->student.surname, str, WORD_LEN);
    }
    else
    {
        printf("Wrang symbols\n");
        return FALSE;
    }

    printf("Input student`s name (without spaces): ");
    if (fgets(str, WORD_LEN, stdin) && !strstr(str, " "))
    {
        del_snl(str);
        strncpy(table->student.name, str, WORD_LEN);
    }
    else
    {
        printf("Wrang symbols\n");
        return FALSE;
    }

    printf("Input student`s group (positive integer): ");
    if (fgets(str, WORD_LEN, stdin))
    {
        del_snl(str);
        if (is_integer(str))
            table->student.group = atoi(str);
        else
        {
            printf("Wrang symbols\n");
            return FALSE;
        }
    }

    printf("Input student`s gender (M/W): ");
    if (fgets(str, WORD_LEN, stdin) && !strstr(str, " ") &&
    (strncmp(str, "M\n", WORD_LEN) == 0 || strncmp(str, "W\n", WORD_LEN) == 0))
    {
        del_snl(str);
        if (strncmp(str, "W", WORD_LEN) == 0)
            table->student.gender = 0;
        else
            table->student.gender = 1;
    }
    else
    {
        printf("Wrang symbols\n");
        return FALSE;
    }

    printf("Input student`s age (positive integer): ");
    if (fgets(str, WORD_LEN, stdin))
    {
        del_snl(str);
        if (is_integer(str))
        {
            table->student.age = atoi(str);
            table->key.age = atoi(str);
            table->key.id = *len;
        }
        else
        {
            printf("Wrang symbols\n");
            return FALSE;
        }
    }

    printf("Input student`s average (maybe float or integer, but positive): ");
    if (fgets(str, WORD_LEN, stdin))
    {
        del_snl(str);
        if (is_double(str))
            table->student.avg_score = atof(str);
        else
        {
            printf("Wrang symbols\n");
            return FALSE;
        }
    }

    printf("Input student`s year entering (positive integer): ");
    if (fgets(str, WORD_LEN, stdin))
    {
        del_snl(str);
        if (is_integer(str))
            table->student.year = atoi(str);
        else
        {
            printf("Wrang symbols\n");
            return FALSE;
        }
    }

    printf("Input where student lives (\"dormitory\" or \"flat\"): ");
    if (!fgets(str, WORD_LEN, stdin))
        return FALSE;
    if (strncmp(str, "dormitory\n", WORD_LEN) == 0)
    {
        del_snl(str);
        table->student.type = 0;
        printf("Input dormitory`s number (positive integer): ");
        if (fgets(str, WORD_LEN, stdin))
        {
            del_snl(str);
            if (is_integer(str))
                table->student.type_housing.dormitory.dormitory = atoi(str);
            else
            {
                printf("Wrang symbols\n");
                return FALSE;
            }
        }

        printf("Input student`s room: ");
        if (fgets(str, WORD_LEN, stdin))
        {
            del_snl(str);
            if (is_integer(str))
                table->student.type_housing.dormitory.room = atoi(str);
            else
            {
                printf("Wrang symbols\n");
                return FALSE;
            }
        }
    }
    else if(strncmp(str, "flat\n", WORD_LEN) == 0)
    {
        del_snl(str);
        table->student.type = 1;
        printf("Input street`s name: ");
        if (fgets(str, WORD_LEN, stdin) && !strstr(str, " "))
        {
            del_snl(str);
            strncpy(table->student.type_housing.flat.street, str, WORD_LEN);
        }
        else
        {
            printf("Wrang symbols\n");
            return FALSE;
        }

        printf("Input hous number (positive integer): ");
        if (fgets(str, WORD_LEN, stdin))
        {
            del_snl(str);
            if (is_integer(str))
                table->student.type_housing.flat.house = atoi(str);
            else
            {
                printf("Wrang symbols\n");
                return FALSE;
            }
        }

        printf("Input flat number (positive integer): ");
        if (fgets(str, WORD_LEN, stdin))
        {
            del_snl(str);
            if (is_integer(str))
                table->student.type_housing.flat.room = atoi(str);
            else
            {
                printf("Wrang symbols\n");
                return FALSE;
            }
        }
    }
    else
    {
        printf("Wrang symbols\n");
        return FALSE;
    }
    arr[*len] = table->student;
    arrk[*len] = table->key;
    (*len)++;
    return TRUE;
}
