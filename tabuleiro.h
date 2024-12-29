/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com o estado do tabuleiro.
 */
#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "raylib.h"

#define LINHAS 6
#define COLUNAS 7
#define PECAS_RAIO 36
#define PECAS_DESLOCAX 27
#define PECAS_DESLOCAY 25
#define TABULEIRO_TAM_X 840
#define TABULEIRO_PECAS_TAM_X1 60
#define TABULEIRO_PECAS_TAM_X2 780
#define TABULEIRO_PECAS_TAM_Y1 80
#define TABULEIRO_PECAS_TAM_Y2 688
#define TABULEIRO_DESLOCAX 60
#define TABULEIRO_DESLOCAY 80

#define COR_FUNDO CLITERAL(Color) {255, 251, 247, 255}

struct Celula {
    int id;
    int corPeca;
    Vector2 posicao;
    float vy;
    bool animando;
};

struct JogoEstado {
    bool vitoria;
    bool empate;
    bool pausado;
};

struct Tabuleiro {
    Celula grid[LINHAS][COLUNAS];
    int linhasLivres[COLUNAS];
    float pecasPosicaoXGrid[COLUNAS][2];
    float pecasPosicaoYGrid[LINHAS][2];
    int corSuporte;
    JogoEstado estado;
};

void tabuleiroEstadoInicial(Tabuleiro &tabuleiro, int corPeca, int corSuporte);
void resetarGrid(Tabuleiro &tabuleiro);
void adicionarPeca(Tabuleiro &tabuleiro, int linha, int coluna, int id, int cor);
void atualizarLinhasLivres(Tabuleiro &tabuleiro, int col);

#endif // TABULEIRO_H
