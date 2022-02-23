#include <stdlib.h>
#include "sort.h"

int compar(const void *p, const void *q)
{
    students_t *a = (students_t *)p;
    students_t *b = (students_t *)q;
    return a->age - b->age;
}

int compark(const void *p, const void *q)
{
    keys_t *a = (keys_t *)p;
    keys_t *b = (keys_t *)q;
    return a->age - b->age;
}

void sort_q(students_t arr[], int len)
{
    qsort(&arr[0], len, sizeof(students_t), compar);
}

void sort_bubble(students_t arr[], int len)
{
    students_t tmp;
    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - 1 - i; j++)
            if (arr[j].age > arr[j + 1].age)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void sort_key_q(keys_t arrk[], int len)
{
    qsort(arrk, len, sizeof(keys_t), compark);
}

void sort_key_bubble(keys_t arrk[], int len)
{
    keys_t tmp;
    for (int i = 0; i < len - 1; i++)
        for (int j = 0; j < len - 1 - i; j++)
            if (arrk[j].age > arrk[j + 1].age)
            {
                tmp = arrk[j];
                arrk[j] = arrk[j + 1];
                arrk[j + 1] = tmp;
            }
}
