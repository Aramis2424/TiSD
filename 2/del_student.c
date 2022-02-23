#include <stdio.h>
#include "del_student.h"

int find_item(keys_t arrk[], int len, int id)
{
    for (int j = 0; j < len; j++)
        if (arrk->id == id)
            return j;
    return -1;
}

void del(students_t arr[], int i, int len, keys_t arrk[])
{
   for (int j = i; j < len - 1; j++)
       arr[j] = arr[j + 1]; //исходный массив
   int k = find_item(arrk, len, i); //массив ключей
   if (k > -1)
       for (int j = k; j < len - 1; j++)
           arrk[j] = arrk[j + 1];
}

int del_student(students_t arr[], int *len, keys_t arrk[], double score)
{
    int flag = 0;
    for (int i = 0; i < *len; i++)
    {
        if (arr[i].avg_score < score)
        {
            flag = 1;
            del(arr, i, *len, arrk);
            (*len)--;
            i--;
        }
    }
    if (!flag)
    {
        printf("There is no student, who have score less then %.1lf, ", score);
        printf("but it's all right\n");
    }
    else
        printf("Deletion completed\n");
    return FALSE;
}
