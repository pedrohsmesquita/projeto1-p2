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
#include "tabuleiro.h"
#include <raylib.h>

int escolherColuna(const Tabuleiro &tabuleiro) {
    bool mouseSobreColuna = false;
    int colunaEscolhida;

    for (int i = 0; i < COLUNAS; i++) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
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
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return colunaEscolhida;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    return -1;
}

void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int coluna) {
    adicionarPeca(tabuleiro, obterLinhaLivre(tabuleiro, coluna), coluna, obterId(jogador), obterCor(jogador));
}
