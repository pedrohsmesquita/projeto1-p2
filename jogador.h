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

struct AnimacaoPeca {
    float x;
    float y;
    float yf;
    float v;
    float a;
};

struct Acao {
    Jogador *autor;
    int linha;
    int col;
    bool concluida;
    AnimacaoPeca animacao;
};

struct FilaAcoes {
    Acao acao[6*7];
    int fim;
    int tam;
};

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, int cor, char *nome);
void removerPeca(Jogador &Jogador);
void filaAcoesEstadoInicial(FilaAcoes &fila);
void adicionarAcao(FilaAcoes &fila, Jogador *autor, int l, int c, float x, float y, float yf, float v, float a);
void removerAcao(FilaAcoes &fila);


#endif // JOGADOR_H
