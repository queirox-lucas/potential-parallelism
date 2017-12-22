#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SIZE 50


int main()
{
    int random1[SIZE][SIZE];
    int random2[SIZE][SIZE];
    int multiply[SIZE][SIZE];
    int i, o,c, d, k, sum = 0;
    double time_spent;

    srand(time(NULL));



    for(o = 0; o<SIZE; o++)
    {   for(i = 0; i<SIZE; i++)
        {
            random1[o][i] = rand()%15;
            //printf("%d ", random1[o][i]);
        }
        //printf("\n");
    }


    for(o = 0; o<SIZE; o++)
    {   for(i = 0; i<SIZE; i++)
        {
            random2[o][i] = rand()%15;
            //printf("%d ", random2[o][i]);
        }
        //printf("\n");
    }
    printf("\n");

    //Sem paralelismo
    clock_t begin = clock();//inicio da execução
    for (c = 0; c < SIZE; c++) {
      for (d = 0; d < SIZE; d++) {
        for (k = 0; k < SIZE; k++) {
          sum = sum + random1[c][k]*random2[k][d];
        }

        multiply[c][d] = sum;
        //printf("%d ", multiply[c][d]);
        sum = 0;
      }
      //printf("\n");
    }
    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTempo gasto sem paralelização: %lf \n\n", time_spent);

      //paralelismo threads = numero de cores da máquina
      clock_t begin_1t = clock();//inicio da execução
      #pragma omp parallel for
      for (c = 0; c < SIZE; c++) {
        for (d = 0; d < SIZE; d++) {
          for (k = 0; k < SIZE; k++) {
            sum = sum + random1[c][k]*random2[k][d];
          }

          multiply[c][d] = sum;
          //printf("%d ", multiply[c][d]);
          sum = 0;
        }

      //printf("\n");
      }

    clock_t end_1t = clock();
    time_spent = (double)(end_1t - begin_1t) / CLOCKS_PER_SEC;
    printf("\nTempo gasto com paralelização: %lf \n\n", time_spent);

    return 0;




  return 0;
}
