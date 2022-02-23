#ifndef ARRAY_H
#define ARRAY_H

#include"structures.h"
#include "timemem.h"

void sim_array(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4);
void queue_arr_push(queue_t *queue, char c_elem);
char queue_arr_pop(queue_t *gueue);

#endif // ARRAY_H
