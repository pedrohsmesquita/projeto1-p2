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
    bool turno;
    char nome[NOME_TAM+1];
};

struct Animacao {
    float x;
    float y;
    float yf;
    float v;
};

struct Acao {
    int id;
    int linha;
    int col;
    Animacao animacao;
};

struct FilaAcoes {
    Acao acao[6*7];
    int inicio;
    int fim;
    int tam;
};

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, int cor, char *nome);
void removerPeca(Jogador &Jogador);
void filaAcoesEstadoInicial(FilaAcoes &fila);
void adicionarAcao(FilaAcoes &fila, int id, int l, int c, float x, float y, float yf, float v);
void removerAcao(FilaAcoes &fila);


#endif // JOGADOR_H
