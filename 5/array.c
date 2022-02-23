#include "array.h"
#include "time.h"
#include "io.h"

void queue_arr_push(queue_t *queue, char c_elem)
{
    char *p_in = queue->p_in;
    
    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) != '\0')
    {
        printf("Queue is full!\n");
    }
    else
    {
        *((char*)queue->p_in) = c_elem;
        if (queue->p_in != queue->up)
        {
            queue->p_in = p_in + 1;
        }
        else
        {
            queue->p_in = queue->low;
        }
    }
}

char queue_arr_pop(queue_t *queue)
{
    char *p_out = queue->p_out;
    char ps;

    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) == '\0')
    {
        printf("Queue is empty!\n");
    }
    else
    {
        ps = *((char*)queue->p_out);
        *((char*)queue->p_out) = '\0';
        if (queue->p_out != queue->up)
        {
            queue->p_out = p_out + 1;
        }
        else
        {
            queue->p_out = queue->low;
        }
    }
    return ps;
}

void sim_array(int n, int interval, times_t t1,
              times_t t2, times_t t3, times_t t4)
{
    queue_t queue1;
    strcpy(queue1.name, "First Queue");
    queue1.count_len = MAX_LEN_QUEUE;
    queue1.size = sizeof(char);
    char *quearr1;
    quearr1 = (char *)malloc(queue1.count_len * sizeof(char));
    queue1.low = quearr1;
    queue1.up = quearr1 + queue1.count_len;
    queue1.p_in = quearr1;
    queue1.p_out = quearr1;
    for (int i = 0; i < queue1.count_len; i++)
        quearr1[i] = '\0';
    queue1.out_req = 0;
    queue1.in_req = 0;
    queue1.count_req = 0;
    queue1.sum_len = 0;
    queue1.sum_time = 0;
    queue1.tmp_len = 0;

    queue_t queue2;
    strcpy(queue2.name, "Second Queue");
    queue2.count_len = MAX_LEN_QUEUE;
    queue2.size = sizeof(char);
    char *quearr2;
    quearr2 = (char *)malloc(queue2.count_len * sizeof(char));
    queue2.low = quearr2;
    queue2.up = quearr2 + queue2.count_len;
    queue2.p_in = quearr2;
    queue2.p_out = quearr2;
    for (int i = 0; i < queue2.count_len; i++)
        quearr2[i] = '\0';
    queue2.out_req = 0;
    queue2.in_req = 0;
    queue2.count_req = 0;
    queue2.sum_len = 0;
    queue2.sum_time = 0;
    queue2.tmp_len = 0;
    int out_queue2 = 0;

    int reqin1 = 0;
    int reqout1 = 0;
    int reqin2 = 0;
    int reqout2 = 0;
    int reqshow = 0;

    double time = 0;
    double timereq1 = 0;
    double timereq2 = 0;
    double timereqobr = 0;
    double alltimeque1 = 0;
    double alltimeque2 = 0;

    //time_t rtime1 = clock();

    int type_queue = 0;

    //начало симуляции
    while (reqout1 < n + 1)
    {
        if ((queue1.p_in == queue1.p_out && *((char*)queue1.p_in) != '\0') ||
            (queue2.p_in == queue2.p_out && *((char*)queue2.p_in) != '\0'))
        {
            printf("Queue is full.\n");
            break;
        }

        if (fabs(timereq1 - 0) < EPS)
            timereq1 = getime(t1);

        if (fabs(timereq2 - 0) < EPS)
            timereq2 = getime(t2);

        if (fabs(timereqobr - 0) < EPS)
        {
            if (!(queue1.p_in == queue1.p_out && *((char*)queue1.p_in) == '\0'))
            {
                timereqobr = getime(t3);
                type_queue = 1;
                queue_arr_pop(&queue1);
                queue1.tmp_len--;
                queue1.sum_len += queue1.tmp_len;
                queue1.count_req++;
                queue1.out_req++;
                alltimeque1 += timereqobr;
            }
            else if (!(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
            {
                timereqobr = getime(t4);
                type_queue = 2;
                queue_arr_pop(&queue2);
                queue2.tmp_len--;
                queue2.sum_len += queue2.tmp_len;
                queue2.count_req++;
                queue2.out_req++;
                alltimeque2 += timereqobr;
            }
        }
        else if (type_queue == 2 && !(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
        {
            queue_arr_push(&queue2, '2');
            queue2.tmp_len++;
            queue2.sum_len += queue2.tmp_len;
            queue2.count_req++;
            queue2.in_req++;
            alltimeque2 -= timereqobr;
            timereqobr = 0;
            out_queue2++;
            continue;
        }
    

        double timemin = 0;

        if (fabs(timereqobr - 0) < EPS)
            if (timereq1 - timereq2 < EPS) // найти минимум из 2х
                timemin = timereq1;
            else
                timemin = timereq2;
        else
        {
            if (timereq2 - timereqobr < EPS) // найти минимум из 3х
                timemin = timereq2; 
            else
                timemin = timereqobr;

            if (timereq1 - timemin < EPS)
                timemin = timereq1;
        }
        
        if (fabs(timemin - timereqobr) < EPS)
        {
            timereqobr = 0;
            if (type_queue == 1)
                reqout1++;
            if (type_queue == 2)
                reqout2++;
        }

        if (reqout1 == n)
            break;
        
        if (fabs(timemin - timereq1) < EPS)
        {
            queue_arr_push(&queue1, '1');
            queue1.tmp_len++;
            queue1.sum_len += queue1.tmp_len;
            queue1.count_req++;
            queue1.in_req++;
            reqin1++;
        }

        if (fabs(timemin - timereq2) < EPS)
        {
            queue_arr_push(&queue2, '2');
            queue2.tmp_len++;
            queue2.sum_len += queue2.tmp_len;
            queue2.count_req++;
            queue2.in_req++;
            reqin2++;
        }

        timereq1 -= timemin;
        timereq2 -= timemin;

        if (timereqobr >= timemin)
            timereqobr -= timemin;
        time += timemin;

        if (reqout1 % interval == 0 && reqout1 != reqshow)
        {
            reqshow = reqout1;
            printf("Done requests: \t %d\n", reqout1);
            len_swow(&queue1);
            len_swow(&queue2);
            printf("\n");
        }

    }
    if (reqout1 == 1000 && reqout1 != reqshow)
    {
        reqshow = reqout1;
        printf("Done requests: \t %d\n", reqout1);
        len_swow(&queue1);
        len_swow(&queue2);
        printf("\n");
    }
    
    //time_t rtime2 = clock();
    //int timerealall = rtime2 - rtime1;

    double avetime_in1 = (t1.max + t1.min) / 2;
    double avetime_out1 = (t3.max + t3.min) / 2;
    //double avetime_in2 = (t2.max + t2.min) / 2;

    double total_avetime_in1 = n * avetime_in1;
    double total_avetime_out1 = n * avetime_out1;

    double totalwork = alltimeque1 + alltimeque2;
    double timewithoutwork = time - totalwork;

    double timemodel;
    if (total_avetime_in1 - total_avetime_out1 > EPS)
        timemodel = total_avetime_in1;
    else
        timemodel = total_avetime_out1;

//    double wait_in1 = time / avetime_in1;
//    double wait_in2 = time / avetime_in2;

    printf("ALL time: %.2lf\n", time);
    printf("Teor time: %.2lf\n", timemodel);

    if (fabs(timemodel - 0) > EPS)
    {
        double per_out = fabs(100 * (time - timemodel) / timemodel);
        printf("Error rate: %.2lf%% \n\n", per_out);
    }
    else
    {
        printf("Error rate time: 0\n\n");
    }
//    printf("AVG work 1 queue: %.2lf\n", avetime_in1);
//    printf("AVG work 2 queue: %.2lf\n", avetime_in2);
    printf("Requests IN 1 queue: %d\n", reqin1);
    printf("Requests OUT 1 queue: %d\n", reqout1);
    printf("Requests IN 2 queue: %d\n", reqin2);
    printf("Requests OUT 2 queue:%d\n", reqout2);
    printf("Thrown requests from 2 queue: %d\n", out_queue2);
    //printf("Real time (msk): %d\n\n", timerealall);

//    if (fabs(wait_in1 - 0) > EPS)
//    {
//        double per_in1 = fabs(100 * (reqin1 - wait_in1) / wait_in1);
//        printf("Error rate 1 queue: \t %.2lf%%\n", per_in1);
//    }
//    else
//    {
//        printf("Error rate 1 queue: 0\n");
//    }

//    if (fabs(wait_in2 - 0) > EPS)
//    {
//        double per_in2 = fabs(100 * (reqin2 - wait_in2) / wait_in2);
//        printf("Error rate 2 queue: \t %.2lf%%\n", per_in2);
//    }
//    else
//    {
//        printf("Error rate 2 queue: 0\n");
//    }
    
    printf("Downtime: %.2lf\n\n", fabs(timewithoutwork));

    free(quearr1);
    free(quearr2);    
}
