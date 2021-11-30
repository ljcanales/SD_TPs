#include "omp.h"
#include "stdio.h"
#include "mytime.h"

#define DECBIN(n, i) ((n & (1 << i)) ? 1 : 0)

/****** Convierte e Imprime ********************/
void conv(int pid, int z) {
    int v[16], i;
    for (i = 0; i < 16; i++)
        v[i] = DECBIN(z, i);
    printf(" %d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d (%d)\n", pid,
           v[15], v[14], v[13],
           v[12], v[11], v[10], v[9], v[8], v[7], v[6], v[5], v[4], v[3], v[2], v[1], v[0], z);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    int i, tid;
    CLOCK_TYPE t_ini, t_fin;
    double tiempoTotal=0.0;
    GETTIME(t_ini);
    #pragma omp parallel num_threads(6) private(tid)
    {
        tid = omp_get_thread_num();
        /*bucle paralelo con openmp y n iteraciones */
        #pragma omp for schedule(dynamic)
        for (i = 0; i < 65536; i++) {
            conv(tid, i);
        }
    }
    GETTIME(t_fin);
    DIFTIME(t_fin,t_ini,tiempoTotal);
    printf("El tiempo total de trabajo es de: %lf\n",tiempoTotal);
    return 0;
}