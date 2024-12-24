/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "render.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "render.h".
 */
#include "render.h"
#include <raylib.h>

void converterIntParaColor(Color &cor, int corInt);
void escurecerCor(Color &corOriginal, Color &cor, float fatorEscurecer);
void desenharSuporte(const Tabuleiro &tabuleiro);
void desenharBaseTabuleiro(const Tabuleiro &tabuleiro);
void desenharPecasTabuleiro(const Tabuleiro &tabuleiro);
Texture2D& carregarTexturaTabuleiro();
void descarregarTexturaTabuleiro();

void desenharTabuleiro(const Tabuleiro &tabuleiro, Mouse &mouse) {
    BeginDrawing();

    ClearBackground(GRAY);
    SetMouseCursor(mouse.tipoCursor);
    desenharSuporte(tabuleiro);
    desenharBaseTabuleiro(tabuleiro);
    desenharPecasTabuleiro(tabuleiro);

    EndDrawing();
}

void converterIntParaColor(Color &cor, int corInt) {
    cor.r = 0xFF & (corInt >> 24);
    cor.g = 0xFF & (corInt >> 16);
    cor.b = 0xFF & (corInt >> 8);
    cor.a = 0xFF & corInt;
}

void escurecerCor(Color &corOriginal, Color &cor, float fatorEscurecer) {
    cor.r = corOriginal.r * fatorEscurecer;
    cor.g = corOriginal.g * fatorEscurecer;
    cor.b = corOriginal.b * fatorEscurecer;
    cor.a = corOriginal.a;
}

void desenharSuporte(const Tabuleiro &tabuleiro) {
    int deslocar = 5;
    Rectangle partePeca, partePecaSombra, pilarEsq, pilarDir;
    Color cor, sombra;

    deslocar = 5;
    /*
    partePeca = {
        TABULEIRO_PECAS_TAM_X1, TABULEIRO_PECAS_TAM_Y1,
        TABULEIRO_PECAS_TAM_X2 - TABULEIRO_PECAS_TAM_X1,
        TABULEIRO_PECAS_TAM_Y2 - TABULEIRO_PECAS_TAM_Y1
    };
    partePecaSombra = {
        TABULEIRO_PECAS_TAM_X1 - deslocar,
        TABULEIRO_PECAS_TAM_Y1 - deslocar,
        TABULEIRO_PECAS_TAM_X2 - TABULEIRO_PECAS_TAM_X1 + deslocar*2,
        TABULEIRO_PECAS_TAM_Y2 - TABULEIRO_PECAS_TAM_Y1 + deslocar*2
    };
    */
    pilarEsq = {
        0, TABULEIRO_DESLOCAY,
        TABULEIRO_DESLOCAX - deslocar, 768 - 90
    };
    pilarDir = {
        TABULEIRO_PECAS_TAM_X2 + deslocar, TABULEIRO_DESLOCAY,
        TABULEIRO_DESLOCAX, 768 - 90
    };
    converterIntParaColor(cor, tabuleiro.corSuporte);
    escurecerCor(cor, sombra, 0.9f);

    DrawRectangleRounded(pilarEsq, 0.35f, 0, cor);
    DrawRectangleRounded(pilarDir, 0.35f, 0, cor);
    /*
    DrawRectangleRounded(partePecaSombra, 0.1, 10, sombra);
    DrawRectangleRounded(partePeca, 0.1f, 10, cor);
    escurecerCor(cor, sombra, 0.95f);
    for (int i = 0; i < COLUNAS; i++) {
        int largura = tabuleiro.pecasPosicaoXGrid[i][1] - tabuleiro.pecasPosicaoXGrid[i][0];
        Rectangle pecasArea = {
            tabuleiro.pecasPosicaoXGrid[i][0] - deslocar*2,
            TABULEIRO_PECAS_TAM_Y1 + deslocar,
            largura + deslocar*4,
            TABULEIRO_PECAS_TAM_Y2 - TABULEIRO_PECAS_TAM_Y1 - deslocar*2
        };
        DrawRectangleRounded(pecasArea, 0.3f, 10, sombra);
    }
    */
}

void desenharBaseTabuleiro(const Tabuleiro &tabuleiro) {
    Texture2D textura = carregarTexturaTabuleiro();
    int desloca = 5;
    Color cor;

    converterIntParaColor(cor, tabuleiro.corSuporte);
    DrawTextureEx(textura, (Vector2){TABULEIRO_PECAS_TAM_X1 - desloca, TABULEIRO_PECAS_TAM_Y1 - desloca}, 0.0f, 1.0f, cor);
}

void desenharPecasTabuleiro(const Tabuleiro &tabuleiro) {
    const float escurecer = 0.85f;
    for (int i = 0; i < LINHAS; i++) {
        int deslocaY = TABULEIRO_PECAS_TAM_Y1 + (PECAS_DESLOCAY + PECAS_RAIO * 2) * i;
        for (int j = 0; j < COLUNAS; j++) {
            Vector2 posCentroPeca = {
                tabuleiro.pecasPosicaoXGrid[j][0] + PECAS_RAIO,
                deslocaY + PECAS_DESLOCAY + PECAS_RAIO,
            };
            Color cor, corEscurecida;
            converterIntParaColor(cor, tabuleiro.grid[i][j].corPeca);
            if (tabuleiro.grid[i][j].id == 0) {
                DrawCircleV(posCentroPeca, PECAS_RAIO, cor);
            } else {
                escurecerCor(cor, corEscurecida, escurecer);
                DrawCircleV(posCentroPeca, PECAS_RAIO, corEscurecida);
                DrawCircleV(posCentroPeca, PECAS_RAIO - 5, cor);
            }
        }
    }
}

Texture2D& carregarTexturaTabuleiro() {
    static Texture2D textura = LoadTexture("assets/base.png");

    return textura;
}

void descarregarTexturaTabuleiro() {
    Texture2D textura = carregarTexturaTabuleiro();

    UnloadTexture(textura);
}
