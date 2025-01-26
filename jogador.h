/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com o estado do jogador.
 */
#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"

#define JOGADOR_1 0
#define JOGADOR_2 1
#define NOME_TAM 12

struct Jogador {
    int id;
    int pecas;
    Color cor;
    bool turno;
    bool vencedor;
    char nome[NOME_TAM+1];
};

void jogadorEstadoInicial(Jogador& jogador, int id, Color cor, char nome[]);
void atualizarNomeCor(Jogador& jogador, const char nome[], const Color cor);
void resetarJogador(Jogador& jogador);
void removerPeca(Jogador& Jogador);



#endif // JOGADOR_H
