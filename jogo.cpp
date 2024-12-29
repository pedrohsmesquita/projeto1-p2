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
#include "raylib.h"

bool checarHorizontal(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
bool checarVertical(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
bool checarDiagonalEsq(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
bool checarDiagonalDir(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
//bool idPecaIdJogador(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna);

void escolherColuna(const Tabuleiro &tabuleiro, Mouse &mouse) {
    bool mouseSobreColuna = false;
    //int colunaEscolhida = -1;

    for (int i = 0; i < COLUNAS; i++) {
        bool mouseSobreTabuleiroY = (mouse.y >= TABULEIRO_PECAS_TAM_Y1 &&
                                     mouse.y <= TABULEIRO_PECAS_TAM_Y2);
        bool mouseSobrePecasTabuleiro = (mouse.x >= tabuleiro.pecasPosicaoXGrid[i][0] &&
                                         mouse.x <= tabuleiro.pecasPosicaoXGrid[i][1]);

        if (mouseSobreTabuleiroY && mouseSobrePecasTabuleiro) {
            mouseSobreColuna = true;
            mouse.estadoEscolhido = i;
            break;
        }
    }
    if (mouseSobreColuna) {
        mouse.tipoCursor = MOUSE_CURSOR_POINTING_HAND;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //mouse.estadoEscolhido = colunaEscolhida;
            mouse.click = true;
        }
    }
}

void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int linha, int coluna) {
    tabuleiro.grid[linha][coluna].corPeca = jogador.cor;
    tabuleiro.grid[linha][coluna].animando = true;
    tabuleiro.grid[linha][coluna].posicao.x = tabuleiro.pecasPosicaoXGrid[coluna][0] + PECAS_RAIO;
    tabuleiro.grid[linha][coluna].posicao.y = -PECAS_RAIO;
    atualizarLinhasLivres(tabuleiro, coluna);
    removerPeca(jogador);
}

void consumarAcao(Celula &celula, const Jogador &jogador1, const Jogador &jogador2, float yf) {
    celula.posicao.y = yf;
    celula.animando = false;
    if (celula.corPeca == jogador1.cor) {
        celula.id = jogador1.id;
    } else {
        celula.id = jogador2.id;
    }
}

void atualizarPosicaoPeca(Celula &celula, float deltaT) {
    const float aceleracao = 2000.0f;

    celula.vy += aceleracao * deltaT;
    celula.posicao.y += celula.vy * deltaT;
}

bool acaoValida(const Tabuleiro &tabuleiro, int coluna) {
    return coluna >= 0 && tabuleiro.linhasLivres[coluna] >= 0;
}

bool verificarVitoria(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]) {
    return checarHorizontal(tabuleiro, linha, coluna, centrosPiPf)   ||
            checarVertical(tabuleiro, linha, coluna, centrosPiPf)    ||
            checarDiagonalEsq(tabuleiro, linha, coluna, centrosPiPf) ||
            checarDiagonalDir(tabuleiro, linha, coluna, centrosPiPf);
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

bool checarHorizontal(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]) {
    int c, freq = 0;
    bool idJogadorIdPeca;

    c = coluna - 3;
    while (c < 0) {
        c++;
    }
    for (; c <= coluna && freq != 4; c += 1 + freq) {
        freq = 0;
        idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[linha][c].id;
        if (idJogadorIdPeca) {
            centrosPiPf[0].x = tabuleiro.pecasPosicaoXGrid[c][0] + PECAS_RAIO;
            centrosPiPf[0].y = tabuleiro.pecasPosicaoYGrid[linha][0] + PECAS_RAIO;
            for (freq = 1; freq < 4; freq++) {
                int col = c + freq;
                idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[linha][col].id;
                if (col >= COLUNAS || !idJogadorIdPeca) {
                    break;
                }
                centrosPiPf[1].x = tabuleiro.pecasPosicaoXGrid[col][0] + PECAS_RAIO;
                centrosPiPf[1].y = tabuleiro.pecasPosicaoYGrid[linha][0] + PECAS_RAIO;
            }
        }
    }

    return freq == 4;
}

bool checarVertical(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]) {
    int l, freq = 0;
    bool idJogadorIdPeca;

    l = linha + 3;
    while (l >= LINHAS) {
        l--;
    }
    for (; l > linha && freq != 4; l = l - 1 - freq) {
        freq = 0;
        idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[l][coluna].id;
        if (idJogadorIdPeca) {
            centrosPiPf[0].x = tabuleiro.pecasPosicaoXGrid[coluna][0] + PECAS_RAIO;
            centrosPiPf[0].y = tabuleiro.pecasPosicaoYGrid[l][0] + PECAS_RAIO;
            for (freq = 1; freq < 4; freq++) {
                int lin = l - freq;
                idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[lin][coluna].id;
                if (lin < 0 || !idJogadorIdPeca) {
                    break;
                }
                centrosPiPf[1].x = tabuleiro.pecasPosicaoXGrid[coluna][0] + PECAS_RAIO;
                centrosPiPf[1].y = tabuleiro.pecasPosicaoYGrid[lin][0] + PECAS_RAIO;
            }
        }
    }

    return freq == 4;
}

bool checarDiagonalEsq(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]) {
    int l = linha, c = coluna, dec = 0, freq = 0;
    bool idJogadorIdPeca;

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
        idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[l][c].id;
        if (idJogadorIdPeca) {
            centrosPiPf[0].x = tabuleiro.pecasPosicaoXGrid[c][0] + PECAS_RAIO;
            centrosPiPf[0].y = tabuleiro.pecasPosicaoYGrid[l][0] + PECAS_RAIO;
            for (freq = 1; freq < 4; freq++) {
                int lin = l - freq;
                int col = c + freq;
                idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[lin][col].id;
                if (lin < 0 || col >= COLUNAS || !idJogadorIdPeca) {
                    break;
                }
                centrosPiPf[1].x = tabuleiro.pecasPosicaoXGrid[col][0] + PECAS_RAIO;
                centrosPiPf[1].y = tabuleiro.pecasPosicaoYGrid[lin][0] + PECAS_RAIO;
            }
        }
    }

    return freq == 4;
}

bool checarDiagonalDir(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]) {
    int l = linha, c = coluna, dec = 0, freq = 0;
    bool idJogadorIdPeca;

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
        idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[l][c].id;
        if (idJogadorIdPeca) {
            centrosPiPf[0].x = tabuleiro.pecasPosicaoXGrid[c][0] + PECAS_RAIO;
            centrosPiPf[0].y = tabuleiro.pecasPosicaoYGrid[l][0] + PECAS_RAIO;
            for (freq = 1; freq < 4; freq++) {
                int lin = l - freq;
                int col = c - freq;
                idJogadorIdPeca = tabuleiro.grid[linha][coluna].id == tabuleiro.grid[lin][col].id;
                if (lin < 0 || col < 0 || !idJogadorIdPeca) {
                    break;
                }
                centrosPiPf[1].x = tabuleiro.pecasPosicaoXGrid[col][0] + PECAS_RAIO;
                centrosPiPf[1].y = tabuleiro.pecasPosicaoYGrid[lin][0] + PECAS_RAIO;
            }
        }
    }

    return freq == 4;
}
/*
bool idPecaIdJogador(const Jogador &jogador, const Tabuleiro &tabuleiro, int linha, int coluna) {
    return tabuleiro.grid[linha][coluna].id == jogador.id;
}
*/
