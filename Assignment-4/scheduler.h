#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    float throughput;
    float average_response_time;
} ScheduleMetrics;

float SJF(int* jobs, int size);
float FIFO(int* jobs, int size);

ScheduleMetrics run_SJF(const int* jobs, int size);
ScheduleMetrics run_FIFO(const int* jobs, int size);

#endif
