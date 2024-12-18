/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "jogador.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "jogador.h". Todas as funções desse arquivo
 * deverão ser responsáveis pela lógica e estado dos jogadores
 */
 #include "jogador.h"
 #include <cstring>

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, int cor, char *nome) {
    jogador.id = id;
    jogador.pecas = pecas;
    jogador.cor = cor;
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

char *obterNome(Jogador &jogador) {
    return jogador.nome;
}

void definirNome(Jogador &jogador, char *nome) {
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

int obterPecas(const Jogador &jogador) {
    return jogador.pecas;
}

void removerPeca(Jogador &jogador) {
    jogador.pecas--;
}

int obterCor(const Jogador &jogador) {
    return jogador.cor;
}

void definirCor(Jogador &jogador, int cor) {
    jogador.cor = cor;
}

int obterId(const Jogador &jogador) {
    return jogador.cor;
}
