/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "jogador.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "jogador.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis pela l�gica e estado do tabuleiro.
 */
#include "tabuleiro.h"

void tabuleiroEstadoInicial(Tabuleiro &tabuleiro, int corPeca, int corSuporte) {
    tabuleiro.corSuporte = corSuporte;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro.grid[i][j].id = 0;
            tabuleiro.grid[i][j].corPeca = corPeca;
        }
    }
    int unidadeDxPeca = PECAS_DESLOCAX + PECAS_RAIO * 2;
    for (int i = 0; i < COLUNAS; i++) {
        tabuleiro.linhasLivres[i] = LINHAS - 1;
        tabuleiro.pecasPosicaoXGrid[i][0] = TABULEIRO_PECAS_TAM_X1 + unidadeDxPeca * i + PECAS_DESLOCAX;
        tabuleiro.pecasPosicaoXGrid[i][1] = tabuleiro.pecasPosicaoXGrid[i][0] + PECAS_RAIO * 2;
    }
}

void adicionarPeca(Tabuleiro &tabuleiro, int linha, int coluna, int id, int cor) {
    tabuleiro.grid[linha][coluna].id = id;
    tabuleiro.grid[linha][coluna].corPeca = cor;
    tabuleiro.linhasLivres[coluna]--;
}
