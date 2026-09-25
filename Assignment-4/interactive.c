#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scheduler.h"

static int split_job_sizes(const char* job_sizes_str, int* job_sizes,
                           int capacity, int* job_count) {
    char* input = malloc(strlen(job_sizes_str) + 1);
    if (input == NULL) {
        fprintf(stderr, "Unable to allocate memory for job input.\n");
        return 0;
    }

    strcpy(input, job_sizes_str);
    *job_count = 0;
    char* token = strtok(input, ",");

    while (token != NULL) {
        char* end = NULL;
        long job_size = strtol(token, &end, 10);

        if (*token == '\0' || *end != '\0' ||
            job_size <= 0 || job_size > INT_MAX) {
            fprintf(stderr, "Invalid job size: %s\n", token);
            free(input);
            return 0;
        }
        if (*job_count == capacity) {
            fprintf(stderr, "Too many jobs; maximum is %d.\n", capacity);
            free(input);
            return 0;
        }

        job_sizes[(*job_count)++] = (int)job_size;
        token = strtok(NULL, ",");
    }

    free(input);
    return *job_count > 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }

    int job_sizes[100];
    int job_count = 0;

    if (!split_job_sizes(argv[2], job_sizes, 100, &job_count)) {
        return 1;
    }

    ScheduleMetrics metrics;
    if (strcmp(argv[1], "FIFO") == 0) {
        metrics = run_FIFO(job_sizes, job_count);
    } else if (strcmp(argv[1], "SJF") == 0) {
        metrics = run_SJF(job_sizes, job_count);
    } else {
        printf("Unknown scheduler type: %s\n", argv[1]);
        return 1;
    }

    printf("Throughput: %.2f jobs/second\n", metrics.throughput);
    printf("Average response time: %.6f seconds\n",
           metrics.average_response_time);

    return 0;
}