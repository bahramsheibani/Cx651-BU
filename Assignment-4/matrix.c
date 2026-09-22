#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_matrix(int rows, int cols, int *matrix) {
     for(int i=0 ; i < rows ; i++)
        for(int j = 0; j < cols; j++)
            matrix[i * cols + j] = rand() % 100;

}
void init_result(int rows, int cols, int *result) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i * cols + j] = 0;
        }
    }
}

void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result) {
    if (cols1 != rows2) {
        fprintf(stderr, "wrong matrix dimensions\n");
        exit(EXIT_FAILURE);
    }
    init_result(rows1, cols2, result);

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }
}

void display_matrix(int rows, int cols, int *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}


float do_job(int rows1, int cols1, int cols2, int forever) {
    int *matrix1 = (int *)malloc(rows1 * cols1 * sizeof(int));
    int *matrix2 = (int *)malloc(cols1 * cols2 * sizeof(int));
    int *result = (int *)malloc(rows1 * cols2 * sizeof(int));

    generate_random_matrix(rows1, cols1, matrix1);
    generate_random_matrix(cols1, cols2, matrix2);

    clock_t start = clock();
    for (int i = 0; i < forever; i++) {
        multiply_matrices(rows1, cols1, matrix1, cols1, cols2, matrix2, result);
    }
    clock_t end = clock();

    float time = (float)(end - start) / CLOCKS_PER_SEC;

    free(matrix1);
    free(matrix2);
    free(result);

    return time;

   
}

