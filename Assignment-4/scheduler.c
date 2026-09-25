#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "scheduler.h"

 float run_jobs(const int* jobs, int size) {
    float elapsed_time = 0.0f;
    float total_response_time = 0.0f;

    if (jobs == NULL || size <= 0) {
        return metrics;
    }

    for (int i = 0; i < size; i++) {
        elapsed_time += do_job(jobs[i], jobs[i], jobs[i], 0);
        total_response_time += elapsed_time;
    }

    float average_response_time = total_response_time / size;
    if (elapsed_time > 0.0f) {
        float throughput = size / elapsed_time;
    }

    return average_response_time;
}

float run_SJF(const int* jobs, int size) {
    float average_response_time = 0.0f;

    if (jobs == NULL || size <= 0) {
        return average_response_time;
    }

    int* sorted_jobs = malloc((size_t)size * sizeof(*sorted_jobs));
    if (sorted_jobs == NULL) {
        fprintf(stderr, "Unable to allocate memory for jobs.\n");
        return average_response_time;
    }

    for (int i = 0; i < size; i++) {
        sorted_jobs[i] = jobs[i];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_jobs[j] > sorted_jobs[j + 1]) {
                int temp = sorted_jobs[j];
                sorted_jobs[j] = sorted_jobs[j + 1];
                sorted_jobs[j + 1] = temp;
            }
        }
    }

    average_response_time = run_jobs(sorted_jobs, size);
    free(sorted_jobs);
    return average_response_time;
}

float FIFO(int* jobs, int size) {
    return run_FIFO(jobs, size).average_response_time;
}

float SJF(int* jobs, int size) {
    return run_SJF(jobs, size).average_response_time;
}
