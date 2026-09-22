
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <rows1> <cols1> <cols2> <run forever? 0/1>\n", argv[0]);
        return 1;
    }

    int rows1 = atoi(argv[1]);
    int cols1 = atoi(argv[2]);
    int cols2 = atoi(argv[3]);

    int run_ = atoi(argv[4]);


    // Check if dimensions are valid for matrix multiplication
    if (rows1 <= 0 || cols1 <= 0 || cols2 <= 0) {
        printf("Dimensions must be positive integers.\n");
        return 1;
    }

    do_job(rows1, cols1,cols2, run_);
    return 0;
}