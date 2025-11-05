// This is a simple matmul in C, we will try to run as fast as possible on cpu
// (then gpu??)

#include <stdio.h>  // for printf
#include <stdlib.h> // for calloc
#include <time.h>   // for time counting to get flops

#ifndef SQUARE_MATRIX_DIMENSION
#define SQUARE_MATRIX_DIMENSION 1024
#endif

// TODO: currently only for 2 matrices, ideally want to multiply n matrices
int matrixMultiply(float *matrix1, float *matrix2, int m1Dimension,
                   int m2Dimension, size_t sizeOfM1, size_t sizeOfM2) {
  int return_code = 0;
  if (sizeOfM1 == sizeOfM2) {
    puts("this is a square matrix");
    // multiplySquareMatrices();
  } else {
    puts("this is a non-square matrix");
    // multiplyNonSquareMatrices();
  }
  return return_code;
}

int main() {
  struct timespec ts, start_ts, end_ts;
  clock_gettime(CLOCK_MONOTONIC, &start_ts);

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

  if (!matrix1 || !matrix2) {
    fprintf(stderr, "Memory allocation for matrix 1 and 2 failed\n");
    return 1;
  }
  printf("Matrix 1 elem 0,0:- %f\nMatrix 2 elem 0,0:- %f\n\n", matrix1[0],
         matrix2[0]);

  // TODO: Multiply matrices here, count number of flop's, divide by timespent to get flops
  matrixMultiply(matrix1, matrix2, SQUARE_MATRIX_DIMENSION, SQUARE_MATRIX_DIMENSION, sizeof(matrix1), sizeof(matrix2));

  clock_gettime(CLOCK_MONOTONIC, &end_ts);
  // Total time spent is time in seconds + nanoseconds since nanoseconds wrap
  // post every second
  unsigned int timespent_nanoseconds = end_ts.tv_nsec - start_ts.tv_nsec;
  unsigned int timespent_seconds = end_ts.tv_sec - start_ts.tv_sec;
  double timespent_absolute =
      timespent_seconds + (timespent_nanoseconds * 1e-9);
  printf("Absolute:- %fs, Seconds:- %ds, Nanoseconds:- %dns\n",
         timespent_absolute, timespent_seconds, timespent_nanoseconds);
  return 0;
}
