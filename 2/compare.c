#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include "sort.h"
#include "read_file.h"
#include "compare.h"
#include "errors.h"

int compare(table_t *ntable, students_t narr[], int *nlen, keys_t narrk[])
{
    int rc;
    rc = read_file(ntable, narr, nlen, narrk);
    if (rc == TOO_BIG_DATA)
    {
        printf("too big data");
        return TOO_BIG_DATA;
    }
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;
    gettimeofday(&tv_start, NULL);
    sort_q(narr, *nlen);
    gettimeofday(&tv_stop, NULL);
    elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);
    printf("qsort table (time): %" PRId64 " us\n", elapsed_time);
    size_t memory = *nlen * sizeof(narr[0]);
    printf("qsort table (memory): %zu bytes\n\n", memory);

    *nlen = 0;
    rc = read_file(ntable, narr, nlen, narrk);
    if (rc == TOO_BIG_DATA)
    {
        printf("too big data");
        return TOO_BIG_DATA;
    }
    gettimeofday(&tv_start, NULL);
    sort_bubble(narr, *nlen);
    gettimeofday(&tv_stop, NULL);
    elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);
    printf("bubble sort table (time): %" PRId64 " us\n", elapsed_time);
    memory = *nlen * sizeof(narr[0]);
    printf("bubble sort table (memory): %zu bytes\n\n", memory);

    *nlen = 0;
    rc = read_file(ntable, narr, nlen, narrk);
    if (rc == TOO_BIG_DATA)
    {
        printf("too big data");
        return TOO_BIG_DATA;
    }
    gettimeofday(&tv_start, NULL);
    sort_key_q(narrk, *nlen);
    gettimeofday(&tv_stop, NULL);
    elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);
    printf("qsort keys (time): %" PRId64 " us\n", elapsed_time);
    memory = *nlen * (sizeof(narr[0]) + sizeof(narrk[0]));
    printf("qsort keys (memory): %zu bytes\n\n", memory);

    *nlen = 0;
    rc = read_file(ntable, narr, nlen, narrk);
    if (rc == TOO_BIG_DATA)
    {
        printf("too big data");
        return TOO_BIG_DATA;
    }
    gettimeofday(&tv_start, NULL);
    sort_key_bubble(narrk, *nlen);
    gettimeofday(&tv_stop, NULL);
    elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);
    printf("bubble sort keys: %" PRId64 " us\n", elapsed_time);
    memory = *nlen * (sizeof(narr[0]) + sizeof(narrk[0]));
    printf("bubble sort keys (memory): %zu bytes\n\n", memory);

    return TRUE;
}
