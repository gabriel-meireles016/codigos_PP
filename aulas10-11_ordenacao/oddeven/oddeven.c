// mpicc oddeven.c
// mpirun a.out n

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int compara_elementos(const void* a, const void* b){
    return (*(int*)b - *(int*)a);
}


// criar as funções minimo_vetor e maximo_vetor
// min fazendo merge ate o N

void par_oddeven(int *A, int n, int rank, int size){
    int B[n];
    MPI_Status status;

    qsort(A, n, sizeof(int), compara_elementos);
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            if (rank % 2 == 0) {
                MPI_Recv(B, n, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, &status);
                MPI_Send(A, n, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
                A = minimo_vetor(A, B, n);
            } else {
                MPI_Recv(A, n, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
                MPI_Send(B, n, MPI_INT, rank - 1, 1, MPI_COMM_WORLD);
                A = maximo_vetor(A, B, n);
            }
            
        } else if (rank > 0 && rank < size - 1){
            if (rank % 2 == 0) {
                MPI_Recv(B, n, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
                MPI_Send(A, n, MPI_INT, rank - 1, 1, MPI_COMM_WORLD);
                A = maximo_vetor(A, B, n);
            } else {
                MPI_Recv(A, n, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, &status);
                MPI_Send(B, n, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
                A = minimo_vetor(A, B, n);
            }
        }
        
    }
    
}

void gerar_vetor(int* A, int n){
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

int main(int argc, char *argv[]) {
    
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
        
    int n = atoi(argv[1]);
    int A[n * size];

    srand(time(0));
    gerar_vetor(A, n * size);


    par_oddeven(A, n, rank, size);
    
    MPI_Finalize();    

    return 0;
}
