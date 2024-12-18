/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com o estado do jogador.
 */
#ifndef JOGADOR_H
#define JOGADOR_H

#define NOME_TAM 15

struct Jogador {
    int id;
    int pecas;
    int cor;
    char nome[NOME_TAM+1];
};

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, int cor, char *nome);
char *obterNome(Jogador &Jogador);
void definirNome(Jogador &jogador, char *nome);
int obterPecas(const Jogador &jogador);
void removerPeca(Jogador &Jogador);
int obterCor(const Jogador &jogador);
void definirCor(Jogador &jogador, int cor);
int obterId(const Jogador &jogador);

#endif // JOGADOR_H
