// gcc broadcast.c -o broadcast -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void broadcast_geral(int d, int id, int source, void* mensagem){
    int id_virtual = id ^ source;
    int mascara = (int)pow(2, d) - 1; // 2 elevado a d -1

    for (int i = 0; i < d - 1; i++) {
        mascara = mascara ^ (int)pow(2, i);
        if (id_virtual == 0 && mascara == 0) {
            if (id_virtual == 0 && (int)pow(2, i) == 0) {
                int destino_virtual = id_virtual ^ (int)pow(2, i);
                int destino_fisico = destino_virtual ^ source;
                //enviar mensagem 
            } else {
                int origem_virtual = id_virtual ^ (int)pow(2, i);
                int origem_fisica = origem_virtual ^ source;
                // receber mensagem
            }
        }
    }
}