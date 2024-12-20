/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "render.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "render.h".
 */
#include "render.h"
#include <raylib.h>

void converterIntParaColor(Color &cor, int corInt);
void desenharSuporte(const Tabuleiro &tabuleiro);
void desenharTabuleiroPecas(const Tabuleiro &tabuleiro);

void desenharTabuleiro(const Tabuleiro &tabuleiro, Mouse &mouse) {
    BeginDrawing();
    ClearBackground(GRAY);
    SetMouseCursor(mouse.tipoCursor);
    desenharSuporte(tabuleiro);
    desenharTabuleiroPecas(tabuleiro);
    EndDrawing();
}

void converterIntParaColor(Color &cor, int corInt) {
    cor.r = 0xFF & (corInt >> 24);
    cor.g = 0xFF & (corInt >> 16);
    cor.b = 0xFF & (corInt >> 8);
    cor.a = 0xFF & corInt;
}

void desenharSuporte(const Tabuleiro &tabuleiro) {
    Color cor;
    converterIntParaColor(cor, tabuleiro.corSuporte);
    DrawRectangle(0, TABULEIRO_DESLOCAY-10, TABULEIRO_DESLOCAX, 768, cor);
    DrawRectangle(TABULEIRO_PECAS_TAM_X2, TABULEIRO_DESLOCAY-10, TABULEIRO_DESLOCAX, 768, cor);
    DrawRectangle(TABULEIRO_PECAS_TAM_X1, TABULEIRO_PECAS_TAM_Y1,
                  TABULEIRO_PECAS_TAM_X2 - TABULEIRO_PECAS_TAM_X1,
                  TABULEIRO_PECAS_TAM_Y2 - TABULEIRO_PECAS_TAM_Y1,
                  cor);
}

void desenharTabuleiroPecas(const Tabuleiro &tabuleiro) {
    Color cor;
    for (int i = 0; i < LINHAS; i++) {
        int deslocaY = TABULEIRO_PECAS_TAM_Y1 + (PECAS_DESLOCAY + PECAS_RAIO * 2) * i;
        for (int j = 0; j < COLUNAS; j++) {
            converterIntParaColor(cor, tabuleiro.grid[i][j].corPeca);
            DrawCircle(tabuleiro.pecasPosicaoXGrid[j][0] + PECAS_RAIO,
                       deslocaY + PECAS_DESLOCAY + PECAS_RAIO,
                       PECAS_RAIO,
                       cor);
        }
    }
}
