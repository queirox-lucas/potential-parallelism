#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SIZE 5

void multiply_matrices_parallelism_outer_loop(int A[SIZE][SIZE], int B[SIZE][SIZE], int num){
  int multiply[SIZE][SIZE];
  int i, o,c, d, k, sum = 0;
  double time_spent;

  clock_t begin = clock();//inicio da execução
  #pragma omp parallel for num_threads(num)
  for (c = 0; c < SIZE; c++) {
    for (d = 0; d < SIZE; d++) {
      for (k = 0; k < SIZE; k++) {
        sum = sum + A[c][k]*B[k][d];
      }

      multiply[c][d] = sum;
      sum = 0;
    }
  }

  clock_t end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("\nTempo gasto com paralelização %d threads: %lf \n", num, time_spent);

}


int main()
{
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int multiply[SIZE][SIZE];
    int i, o,c, d, k, sum = 0;
    double time_spent;

    srand(time(NULL));


    //Matrix A
    for(o = 0; o<SIZE; o++)
    {   for(i = 0; i<SIZE; i++)
        {
            A[o][i] = rand()%15;
        }
    }

    //Matrix B
    for(o = 0; o<SIZE; o++)
    {   for(i = 0; i<SIZE; i++)
        {
            B[o][i] = rand()%15;
        }

    }
    printf("\n");

    //Do  A*B with no parallelism
    clock_t begin = clock();
    for (c = 0; c < SIZE; c++) {
      for (d = 0; d < SIZE; d++) {
        for (k = 0; k < SIZE; k++) {
          sum = sum + A[c][k]*B[k][d];
        }

        multiply[c][d] = sum;
        printf("%d ", multiply[c][d]);
        sum = 0;
      }
      printf("\n");
    }
    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTempo gasto sem paralelização: %lf \n\n", time_spent);

    //outer loop parallelism
    multiply_matrices_parallelism_outer_loop(A, B, 1);
    multiply_matrices_parallelism_outer_loop(A, B, 2);
    multiply_matrices_parallelism_outer_loop(A, B, 4);
    multiply_matrices_parallelism_outer_loop(A, B, 8);
    multiply_matrices_parallelism_outer_loop(A, B, 16);
    multiply_matrices_parallelism_outer_loop(A, B, 32);
    multiply_matrices_parallelism_outer_loop(A, B, 64);
    multiply_matrices_parallelism_outer_loop(A, B, 128);



  return 0;
}
