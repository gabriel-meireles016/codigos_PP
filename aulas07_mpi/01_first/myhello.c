// mpicc myhello.c
// mpirun -np <qtd> a.out
// mpirun -oversubscribe -np <qtd> a.out
//      Isso permite o uso de mais processadores
// mpirun -hostfile myhost.txt -np <qtd> a.out
//      altera o numero de slots possiveis de processos e processadores

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    
    int npes, myrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    printf("Processo %d de %d processadores, aoba!\n", myrank, npes);
    MPI_Finalize();
}
