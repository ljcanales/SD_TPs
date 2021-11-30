#include <omp.h>
#include "stdio.h"

#define N 10
#define CANT_THREADS 5

int main(int argc, char **argv) {
    int tid, nt, origen, destino = -1;
    int MSM[N], i, ndat;
    for (i = 0; i < N; i++)
        MSM[i] = 0;
    #pragma omp parallel num_threads(CANT_THREADS) private(nt, tid) shared(MSM)
    {
        tid = omp_get_thread_num();
        /*SI es el thread 0*/
        if (tid == 0) {
            ndat = rand() % N;
            for (i = 0; i < ndat; i++)
                MSM[i] = i;
            destino = 1;
            origen = tid;
        }
        else {
            /*Detectar si se envió el mje*/
            while(destino != 1);
            if (destino == 1) {
                printf("th%d recibe MSM de th%d: ndat %d \n\n",tid,origen, ndat);
                for (i = 0; i < ndat; i++)
                    printf("%4d", MSM[i]);
                printf("\n\n");
            }
        }
    }
    return 0;
}
