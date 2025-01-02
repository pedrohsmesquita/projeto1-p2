/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os prot�tipos das fun��es, ambos diretamente
 * relacionados com o estado do jogador.
 */
#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

#define NOME_TAM 15

struct Jogador {
    int id;
    int pecas;
    Color cor;
    bool turno;
    bool vencedor;
    char nome[NOME_TAM+1];
};

void jogadorEstadoInicial(Jogador &jogador, int id, Color cor, char *nome);
void resetarJogador(Jogador &jogador);
void removerPeca(Jogador &Jogador);



#endif // JOGADOR_H
