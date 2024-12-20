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

bool checarHorizontal(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarVertical(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarDiagonalEsq(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool checarDiagonalDir(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);
bool idPecaIdJogador(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);

void escolherColuna(const Tabuleiro &tabuleiro, Mouse &mouse) {
    bool mouseSobreColuna = false;
    int colunaEscolhida = -1;

    for (int i = 0; i < COLUNAS; i++) {
        bool mouseSobreTabuleiroY = (mouse.y >= TABULEIRO_PECAS_TAM_Y1 &&
                                     mouse.y <= TABULEIRO_PECAS_TAM_Y2);
        bool mouseSobrePecasTabuleiro = (mouse.x >= tabuleiro.pecasPosicaoXGrid[i][0] &&
                                         mouse.x <= tabuleiro.pecasPosicaoXGrid[i][1]);

        if (mouseSobreTabuleiroY && mouseSobrePecasTabuleiro) {
            mouseSobreColuna = true;
            colunaEscolhida = i;
            break;
        }
    }
    if (mouseSobreColuna) {
        mouse.tipoCursor = MOUSE_CURSOR_POINTING_HAND;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse.estadoEscolhido = colunaEscolhida;
        }
    }
}

void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int linha, int coluna) {
    adicionarPeca(tabuleiro, linha, coluna, jogador.id, jogador.cor);
    removerPeca(jogador);
}

bool acaoValida(const Tabuleiro &tabuleiro, int coluna) {
    return coluna >= 0 && tabuleiro.linhasLivres[coluna] >= 0;
}

bool verificarVitoria(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    return checarHorizontal(jogador, tabuleiro, linha, coluna)   ||
            checarVertical(jogador, tabuleiro, linha, coluna)    ||
            checarDiagonalEsq(jogador, tabuleiro, linha, coluna) ||
            checarDiagonalDir(jogador, tabuleiro, linha, coluna);
}

bool empate(const Jogador &jogador1, const Jogador &jogador2) {
    return jogador1.pecas == 0 && jogador2.pecas == 0;
}

Jogador *definirTurno(Jogador &jogador) {
    jogador.turno = !jogador.turno;
    return &jogador;
}

Jogador *trocarTurno(Jogador &jogador1, Jogador &jogador2) {
    if (jogador1.turno) {
        jogador1.turno = !jogador1.turno;
        return definirTurno(jogador2);
    } else {
        jogador2.turno = !jogador2.turno;
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
    int l = linha, c = coluna, dec = 0, freq = 0;

    while (dec < 3 && c >= 0 && l < LINHAS) {
        c--;
        l++;
        dec++;
    }
    if (dec != 3 || c < 0 || l >= LINHAS) {
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
    int l = linha, c = coluna, dec = 0, freq = 0;

    while (dec < 3 && c < COLUNAS && l < LINHAS) {
        c++;
        l++;
        dec++;
    }
    if (dec != 3 || c >= COLUNAS || l >= LINHAS) {
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
    return tabuleiro.grid[linha][coluna].id == jogador.id;
}
