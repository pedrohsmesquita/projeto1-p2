/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "jogo.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "jogo.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis por manipular quest�es de coloca��o de pe�as,
 * controle de estados dos jogadores e do tabuleiro (verificando vit�rias,
 * empates, etc), utilizando da modulariza��o proporcionada por jogador.h e
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
