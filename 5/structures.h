#ifndef SRUCTURES
#define SRUCTURES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define MAX_LEN_QUEUE 100000
#define EPS 1e-7


#define TRUE 1
#define FALSE 0
#define OK   0

#define INPUT_ERR 1
#define FILE_OPEN_ERR 2
#define FILE_tEAD_ERR 3
#define DONT_INT_NUM_CHOICE 4
#define INV_NUM_CHOICE 5

typedef struct queue
{
    char name[30];
    void* low;
    void* up;
    void* p_in;
    void* p_out;
    int count_len;
    size_t size;
    int count_req;
    int sum_len;
    int tmp_len;
    int sum_time;
    int out_req;
    int in_req;
} queue_t;

typedef struct node
{
    char inf;
    struct node *next;
} node_t;

typedef struct times
{
    double min;
    double max;
} times_t;


#endif
