/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "jogador.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "jogador.h". Todas as funções desse arquivo
 * deverão ser responsáveis pela lógica e estado do tabuleiro.
 */
#include "tabuleiro.h"

void tabuleiroEstadoInicial(Tabuleiro &tabuleiro, Color corSuporte) {
    tabuleiro.corSuporte = corSuporte;
    int unidadeDxPeca = PECAS_DESLOCAX + PECAS_RAIO * 2;
    for (int i = 0; i < COLUNAS; i++) {
        tabuleiro.linhasLivres[i] = LINHAS - 1;
        tabuleiro.pecasPosicaoXGrid[i][0] = TABULEIRO_PECAS_TAM_X1 + unidadeDxPeca * i + PECAS_DESLOCAX;
        tabuleiro.pecasPosicaoXGrid[i][1] = tabuleiro.pecasPosicaoXGrid[i][0] + PECAS_RAIO * 2;
    }
    for (int i = 0; i < LINHAS; i++) {
        tabuleiro.pecasPosicaoYGrid[i][0] = TABULEIRO_PECAS_TAM_Y1 + PECAS_DESLOCAY + (PECAS_DESLOCAY + PECAS_RAIO * 2) * i;
        tabuleiro.pecasPosicaoYGrid[i][1] = tabuleiro.pecasPosicaoYGrid[i][0] + PECAS_RAIO*2;
    }
}

void resetarGrid(Tabuleiro &tabuleiro) {
    for (int i = 0; i < COLUNAS; i++) {
        tabuleiro.linhasLivres[i] = LINHAS - 1;
    }
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            tabuleiro.grid[i][j].id = 0;
            tabuleiro.grid[i][j].corPeca = CLITERAL(Color) {255, 251, 247, 255};
            tabuleiro.grid[i][j].posicao.x = tabuleiro.pecasPosicaoXGrid[j][0] + PECAS_RAIO;
            tabuleiro.grid[i][j].posicao.y = tabuleiro.pecasPosicaoYGrid[i][0] + PECAS_RAIO;
            tabuleiro.grid[i][j].animando = false;
            tabuleiro.grid[i][j].vy = 0.0f;
        }
    }
    tabuleiro.estado.empate = false;
    tabuleiro.estado.vitoria = false;
    tabuleiro.estado.pausado = false;
}

void adicionarPeca(Tabuleiro &tabuleiro, int linha, int coluna, int id, Color cor) {
    tabuleiro.grid[linha][coluna].id = id;
    tabuleiro.grid[linha][coluna].corPeca = cor;
}

void atualizarLinhasLivres(Tabuleiro &tabuleiro, int col) {
    tabuleiro.linhasLivres[col]--;
}
