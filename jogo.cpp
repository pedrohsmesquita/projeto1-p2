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

bool checarHorizontal(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarVertical(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarDiagonalEsq(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarDiagonalDir(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool idPecaIdJogador(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);

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

void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int linha, int coluna) {
    adicionarPeca(tabuleiro, linha, coluna, obterId(jogador), obterCor(jogador));
    removerPeca(jogador);
}

bool acaoValida(const Tabuleiro &tabuleiro, int coluna) {
    return coluna >= 0 && obterLinhaLivre(tabuleiro, coluna) >= 0;
}

bool verificarVitoria(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    return checarHorizontal(jogador, tabuleiro, linha, coluna)   ||
            checarVertical(jogador, tabuleiro, linha, coluna)    ||
            checarDiagonalEsq(jogador, tabuleiro, linha, coluna) ||
            checarDiagonalDir(jogador, tabuleiro, linha, coluna);
}

bool empate(const Jogador &jogador1, const Jogador &jogador2) {
    return obterPecas(jogador1) == 0 && obterPecas(jogador2) == 0;
}

Jogador *definirTurno(Jogador &jogador) {
    definirTurnoJogador(jogador);
    return &jogador;
}

Jogador *trocarTurno(Jogador &jogador1, Jogador &jogador2) {
    if (obterTurnoJogador(jogador1)) {
        definirTurnoJogador(jogador1);
        return definirTurno(jogador2);
    } else {
        definirTurnoJogador(jogador2);
        return definirTurno(jogador1);
    }
}

bool checarHorizontal(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    int c, freq = 0;

    c = coluna - 3;
    while (c < 0) {
        c++;
    }
    for (; c <= coluna && freq != 4; c += 1 + freq) {
        freq = 0;
        if (idPecaIdJogador(jogador, tabuleiro, linha, c)) {
            for (freq = 1; freq < 4; freq++) {
                if (c + freq >= COLUNAS || !idPecaIdJogador(jogador, tabuleiro, linha, c + freq)) {
                    break;
                }
            }
        }
    }

    return freq == 4;
}

bool checarVertical(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    int l, freq = 0;

    l = linha + 3;
    while (l >= LINHAS) {
        l--;
    }
    for (; l > linha && freq != 4; l = l - 1 - freq) {
        freq = 0;
        if (idPecaIdJogador(jogador, tabuleiro, l, coluna)) {
            for (freq = 1; freq < 4; freq++) {
                if (l - freq < 0 || !idPecaIdJogador(jogador, tabuleiro, l - freq, coluna)) {
                    break;
                }
            }
        }
    }

    return freq == 4;
}

bool checarDiagonalEsq(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    int l = linha, c = coluna, dec = 0, freq;

    while (dec < 3 && c >= 0 && l < LINHAS) {
        c--;
        l++;
        dec++;
    }
    if (dec != 3) {
        c++;
        l--;
    }
    for (; c <= coluna && l >= linha && freq != 4; c += 1 + freq, l = l - 1 - freq) {
        freq = 0;
        if (idPecaIdJogador(jogador, tabuleiro, l, c)) {
            for (freq = 1; freq < 4; freq++) {
                if (l - freq < 0 || c + freq >= COLUNAS || !idPecaIdJogador(jogador, tabuleiro, l - freq, c + freq)) {
                    break;
                }
            }
        }
    }

    return freq == 4;
}

bool checarDiagonalDir(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    int l = linha, c = coluna, dec = 0, freq;

    while (dec < 3 && c < COLUNAS && l < LINHAS) {
        c++;
        l++;
        dec++;
    }
    if (dec != 3) {
        c--;
        l--;
    }
    for (; c >= coluna && l >= linha && freq != 4; c = c - 1 - freq, l = l - 1 - freq) {
        freq = 0;
        if (idPecaIdJogador(jogador, tabuleiro, l, c)) {
            for (freq = 1; freq < 4; freq++) {
                if (l - freq < 0 || c - freq < 0 || !idPecaIdJogador(jogador, tabuleiro, l - freq, c - freq)) {
                    break;
                }
            }
        }
    }

    return freq == 4;
}

bool idPecaIdJogador(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    return obterIdPecaGrid(tabuleiro, linha, coluna) == obterId(jogador);
}
