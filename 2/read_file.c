#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "errors.h"
#include "read_file.h"
#include "functions.h"

#define FILE_NAME "datasuper.txt"

int read_file(table_t *table, students_t arr[], int *len, keys_t arrk[])
{
    FILE *f = NULL;
    //printf("Input name of file: ");
    //char file_name[WORD_LEN];
    //scanf("%s", file_name);
    //f = fopen(file_name, "r");
    f = fopen(FILE_NAME, "r");
    if (f == NULL)
    {
        printf("Sorry, but there is not such file\n");
        return ERROR_OPENING_FILE;
    }
    char line[LINE_LEN];
    char *now_line;
    int n = *len;
    while (fgets(line, LINE_LEN, f))
    {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        now_line = strtok(line, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (isdigit(now_line[i]))
                return INCORRECT_DATA;
        strncpy(table->student.surname, now_line, WORD_LEN);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (isdigit(now_line[i]))
                return INCORRECT_DATA;
        strncpy(table->student.name, now_line, WORD_LEN);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (!isdigit(now_line[i]))
                return INCORRECT_DATA;
        table->student.group = atoi(now_line);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (atoi(now_line) != 1 && atoi(now_line) != 0)
                return INCORRECT_DATA;
        table->student.gender = atoi(now_line);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (!isdigit(now_line[i]))
                return INCORRECT_DATA;
        table->student.age = atoi(now_line);
        table->key.age = atoi(now_line);
        table->key.id = n;

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (!is_double(now_line))
                return INCORRECT_DATA;
        table->student.avg_score = atof(now_line);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (!isdigit(now_line[i]))
                return INCORRECT_DATA;
        table->student.year = atoi(now_line);

        now_line = strtok(NULL, " ");
        for (int i = 0; now_line[i] != '\0'; i++)
            if (atoi(now_line) != 1 && atoi(now_line) != 0)
                return INCORRECT_DATA;
        table->student.type = atoi(now_line);
        if (atoi(now_line) == 1)
        {
            now_line = strtok(NULL, " ");
            for (int i = 0; now_line[i] != '\0'; i++)
                if (isdigit(now_line[i]))
                    return INCORRECT_DATA;
            strncpy(table->student.type_housing.flat.street, now_line, WORD_LEN);

            now_line = strtok(NULL, " ");
            for (int i = 0; now_line[i] != '\0'; i++)
                if (!isdigit(now_line[i]))
                    return INCORRECT_DATA;
            table->student.type_housing.flat.house = atoi(now_line);

            now_line = strtok(NULL, " ");
            for (int i = 0; now_line[i] != '\0'; i++)
                if (!isdigit(now_line[i]))
                    return INCORRECT_DATA;
            table->student.type_housing.flat.room = atoi(now_line);
        }
        else
        {
            now_line = strtok(NULL, " ");
            for (int i = 0; now_line[i] != '\0'; i++)
                if (!isdigit(now_line[i]))
                    return INCORRECT_DATA;
            table->student.type_housing.dormitory.dormitory = atoi(now_line);

            now_line = strtok(NULL, " ");
            for (int i = 0; now_line[i] != '\0'; i++)
                if (!isdigit(now_line[i]))
                    return INCORRECT_DATA;
            table->student.type_housing.dormitory.room = atoi(now_line);
        }
        arr[n] = table->student;
        arrk[n] = table->key;
        n++;
        if (n == ARR_SIZE)
        {
            printf("Sorry, but array is full ");
            (*len) = 0;
            return TOO_BIG_DATA;
        }
    }
    (*len) = n;
    fclose(f);
    return TRUE;
}
