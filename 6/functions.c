#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include "functions.h"
#include "errors.h"

int is_num(const char *str)
{
    int flag = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]) && flag)
            return FALSE;
        else
            if (str[i] == '-')
                flag = 1;
    }

    return TRUE;
}

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int64_t getFileSize(const char* file_name)
{
    int64_t _file_size = 0;
    FILE* fd = fopen(file_name, "rb");

    if(fd == NULL)
    {
        _file_size = -1;
    }
    else
    {
        while(getc(fd) != EOF)
            _file_size++;
        fclose(fd);
    }
    return _file_size;
}

int next_prime(int n)
{
    int k = n + 1;
    while(TRUE)
    {
        for (int i = 2; i < k; i++)
            if (k % i == 0)
            {
                k++;
                continue;
            }
        return k;
    }
}

int prev_prime(int n)
{
    int k = n - 1;
    while(TRUE)
    {
        for (int i = 2; i < k; i++)
            if (k % i == 0)
            {
                k--;
                continue;
            }
        return k;
    }
}
