/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com o estado do tabuleiro.
 */
#ifndef TABULEIRO_H
#define TABULEIRO_H

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

struct Grid {
    int id;
    int corPeca;
};

struct Tabuleiro {
    Grid grid[LINHAS][COLUNAS];
    int linhasLivres[COLUNAS];
    int pecasPosicaoXGrid[COLUNAS][2];
    int corSuporte;
};

void tabuleiroEstadoInicial(Tabuleiro &tabuleiro, int corPeca, int corSuporte);
void adicionarPeca(Tabuleiro &tabuleiro, int linha, int coluna, int id, int cor);
int obterLinhaLivre(const Tabuleiro &tabuleiro, int coluna);
int obterIdPecaGrid(const Tabuleiro &tabuleiro, int linha, int coluna);
int obterCorPecaGrid(const Tabuleiro &tabuleiro, int linha, int coluna);
int obterCorSuporte(const Tabuleiro &tabuleiro);
int obterPecaPosicaoXGrid(const Tabuleiro &tabuleiro, int coluna, int i);

#endif // TABULEIRO_H
