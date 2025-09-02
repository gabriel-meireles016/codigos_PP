#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    
    int a[10], b[10], npes, myrank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank%2 == 1) {
        MPI_Send(a, 10, MPI_INT, (myrank+1)%npes, 1, MPI_COMM_WORLD);
        MPI_Recv(b, 10, MPI_INT, (myrank-1+npes)%npes, 1, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(b, 10, MPI_INT, (myrank-1+npes)%npes, 1, MPI_COMM_WORLD, &status);
        MPI_Send(a, 10, MPI_INT, (myrank+1)%npes, 1, MPI_COMM_WORLD);
    }

    for (int i = 0; i < 10; i++) {
        printf("A = %d\n", a[i]);
        printf("B = %d\n", b[i]);
    }

    //printf("Processo %d de %d processadores, aoba!\n", myrank, npes);
    MPI_Finalize();
}
