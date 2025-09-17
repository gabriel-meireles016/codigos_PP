// gcc broadcast.c -o broadcast -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char mensagem[100][100];
    int num_msg;
} conjunto_msg;

void broadcast_alltoall_malha(int id, char* minha_msg, int p, conjunto_msg* resultado){
    int esq = id - (id % (int)sqrt(p)) + ((id - 1) % (int)sqrt(p));
    int dir = id - (id % (int)sqrt(p)) + ((id + 1) % (int)sqrt(p));
    
    resultado->num_msg = 1;
    strcpy(resultado->mensagem[0], minha_msg);

    // - Comunicação nas Linhas
    printf("=== Nó %d: Fase de comunicação em linhas ===\n", id);

    // -- Calculando coordenada do nó atual
    int lin = id / (int)sqrt(p);
    int col = id % (int)sqrt(p);

    // -- Calculando vizinho esquerdo
    int

    
}

int main(int argc, char const *argv[]) {

    return 0;
}
