// gcc broadcast.c -o broadcast -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    char mensagem[100][100];
    int num_msg;
} conjunto_msg;

void broadcast_alltoall(int id, char* minha_msg, int p, conjunto_msg* resultado){
    int esq = (id - 1) % p;
    
    int dir = (id + 1) % p;
    
    resultado->num_msg = 1;
    strcpy(resultado->mensagem[0], minha_msg);

    conjunto_msg msg;
    msg.num_msg = 1;
    strcpy(msg.mensagem[0], minha_msg);

    for (int i = 1; i < p; i++) {
        // enviar mensagem para vizinho direito
        // send(right, msg)
        printf("No %d enviando %d mensagens para o no %d\n", id, msg.num_msg, dir);

        // receber mensagem da esquerda
        conjunto_msg msg_recebida;
        // receive(left, msg_recebida)
        printf("No %d recebeu %d mensagens do no %d\n\n", id, msg.num_msg, esq);
        msg_recebida = msg;

        for (int j = 0; j < msg_recebida.num_msg; j++) {
            strcpy(resultado->mensagem[resultado->num_msg], msg_recebida.mensagem[j]);
            resultado->num_msg++;
        }

        msg = msg_recebida;
    }
}

// Função auxiliar para imprimir o resultado
void mostrar_resultado(int my_id, conjunto_msg* result) {
    printf("Nó %d possui %d mensagens:\n", my_id, result->num_msg);
    for (int i = 0; i < result->num_msg; i++) {
        printf("  %d: %s\n", i, result->mensagem[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int p = 4; // Número de nós no anel
    conjunto_msg resultados[4]; // Resultados para cada nó
    
    // Mensagens iniciais de cada nó
    char* mensagens_iniciais[4] = {
        "Mensagem do nó 0",
        "Mensagem do nó 1",
        "Mensagem do nó 2",
        "Mensagem do nó 3"
    };
    
    // Simula a execução em cada nó
    for (int id = 0; id < p; id++) {
        printf("\n=== Processando nó %d ===\n", id);
        broadcast_alltoall(id, mensagens_iniciais[id], p, &resultados[id]);
        mostrar_resultado(id, &resultados[id]);
    }
    return 0;
}
