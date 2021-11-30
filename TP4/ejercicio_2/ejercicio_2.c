#include <mpi.h>
#include <omp.h>
#include <iostream>

#define N 10
int main(int argc, char **argv)
{
    int tid, nt, origen, destino = -1;
    int MSM[N], i, ndat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nt);
    for (i = 0; i < N; i++)
        MSM[i] = 0;
#pragma omp parallel num_threads(3) private(nt, tid)
    {
        tid = omp_get_thread_num();
        /*SI es el thread 0*/
        if (tid == 0)
        {
            ndat = rand() % N;
            for (i = 0; i < ndat; i++)
                MSM[i] = i;
            destino = 1;
            for(int i=1;i<omp_get_num_threads();i++){
                MPI_Send(&MSM, ndat, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
            origen = tid;
            /* Enviar al th1 MSM */
        }
        else {
            /*Detectar si se envió el mje*/
            if (destino == 1) {
                MPI_Recv(&MSM, ndat, MPI_INT, 0, tid ,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            }
            printf("th%d recibe MSM de th%d: ndat %d \n\n",tid,origen, ndat);
            for (i = 0; i < ndat; i++)
                printf("%4d", MSM[i]);
            printf("\n\n");
        }
    }
    return 0;
}
