// This is a simple matmul in C, we will try to run as fast as possible on cpu
// (then gpu??)

#include <stdio.h>  // for printf
#include <stdlib.h> // for calloc
#include <time.h>   // for time counting to get flops

#ifndef SQUARE_MATRIX_DIMENSION
#define SQUARE_MATRIX_DIMENSION 1024
#endif

long long matrixMultiply(float *matrix1, float *matrix2, int m1Rows,
                         int m1Columns, int m2Rows, int m2Columns,
                         size_t sizeOfM1, size_t sizeOfM2) {
  long long flop_count = 2LL * m1Rows * m1Columns * m2Columns;
  if (m1Columns != m2Rows) {
    puts("unable to multiply these matrices");
    return -1LL;
  }
  float *resultMatrix =
      calloc((size_t)m1Rows * (size_t)m2Columns, sizeof(float));
  for (int i = 0; i < m1Rows; i++) {
    for (int j = 0; j < m2Columns; j++) {
      float sum = 0.0f;
      for (int k = 0; k < (m1Columns /** or m2Rows */); k++) {
        sum += matrix1[i * m1Columns + k] * matrix2[k * m2Columns + j];
      }
      resultMatrix[i * m2Columns + j] = sum;
    }
  }
  return flop_count;
}

int main() {
  struct timespec ts, start_ts, end_ts;
  printf("Size of square matrix is:- %dx%d\n", SQUARE_MATRIX_DIMENSION,
         SQUARE_MATRIX_DIMENSION);

  /** callocing (contiguous allocation) since above 8MB doesn't fit on stack
    difference between calloc and malloc is malloc doesn't initialise
    calloc is called like (num elements, sizeof each element, slower since mem
    inits 0s) malloc is just (size of bytes you want, faster since no mem
    init'ing)
   */
  float *matrix1 = calloc(
      (size_t)SQUARE_MATRIX_DIMENSION * SQUARE_MATRIX_DIMENSION, sizeof(float));
  float *matrix2 = calloc(
      (size_t)SQUARE_MATRIX_DIMENSION * SQUARE_MATRIX_DIMENSION, sizeof(float));

  // Fill matrix1 & matrix2 with randoms
  srand(time(NULL));
  for (size_t i = 0;
       i < (size_t)SQUARE_MATRIX_DIMENSION * SQUARE_MATRIX_DIMENSION; i++) {
    matrix1[i] = (float)rand() / RAND_MAX;
    matrix2[i] = (float)rand() / RAND_MAX;
  }
  if (!matrix1 || !matrix2) {
    fprintf(stderr, "Memory allocation for matrix 1 and 2 failed\n");
    return 1;
  }
  printf("Matrix 1 elem 0,0:- %f\nMatrix 2 elem 0,0:- %f\n\n", matrix1[0],
         matrix2[0]);

  clock_gettime(CLOCK_MONOTONIC, &start_ts); // Start timing for flops/s

  long long flop_count =
      matrixMultiply(matrix1, matrix2, SQUARE_MATRIX_DIMENSION,
                     SQUARE_MATRIX_DIMENSION, SQUARE_MATRIX_DIMENSION,
                     SQUARE_MATRIX_DIMENSION, sizeof(matrix1), sizeof(matrix2));
  if (flop_count == -1) {
    puts("error multiplying matrices");
  }
  printf("FLOP's:- %llu\n", flop_count);

  clock_gettime(CLOCK_MONOTONIC, &end_ts); // End time for flops/s

  long long timespent_seconds = end_ts.tv_sec - start_ts.tv_sec;

  printf("Time Spent Seconds:- %llus\n", timespent_seconds);
  printf("FLOPS (Floating Point Operations Per Second) = %.3e\n",
         ((double)flop_count / (double)timespent_seconds));

  return 0;
}
