/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "jogo.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "jogo.h". Todas as funções desse arquivo
 * deverão ser responsáveis por manipular questões de colocação de peças,
 * controle de estados dos jogadores e do tabuleiro (verificando vitórias,
 * empates, etc), utilizando da modularização proporcionada por jogador.h e
 * tabuleiro.h.
 */
#include "jogo.h"
#include <raylib.h>

void escolherColuna(const Tabuleiro &tabuleiro, Mouse &mouse) {
    bool mouseSobreColuna = false;
    int colunaEscolhida = -1;

    for (int i = 0; i < COLUNAS; i++) {
        int mouseX = obterMouseX(mouse);
        int mouseY = obterMouseY(mouse);
        bool mouseSobreTabuleiroY = (mouseY >= TABULEIRO_PECAS_TAM_Y1 &&
                                     mouseY <= TABULEIRO_PECAS_TAM_Y2);
        bool mouseSobrePecasTabuleiro = (mouseX >= obterPecaPosicaoXGrid(tabuleiro, i, 0) &&
                                         mouseX <= obterPecaPosicaoXGrid(tabuleiro, i, 1));

        if (mouseSobreTabuleiroY && mouseSobrePecasTabuleiro) {
            mouseSobreColuna = true;
            colunaEscolhida = i;
            break;
        }
    }
    if (mouseSobreColuna) {
        definirTipoCursor(mouse, MOUSE_CURSOR_POINTING_HAND);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            definirMouseEstado(mouse, colunaEscolhida);
        }
    }
}

void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int coluna) {
    adicionarPeca(tabuleiro, obterLinhaLivre(tabuleiro, coluna), coluna, obterId(jogador), obterCor(jogador));
}

bool acaoValida(const Tabuleiro &tabuleiro, int coluna) {
    return coluna >= 0 && obterLinhaLivre(tabuleiro, coluna) >= 0;
}
