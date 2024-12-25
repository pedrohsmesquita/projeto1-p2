/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "render.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "render.h".
 */
#include "render.h"
#include "raylib.h"

void converterIntParaColor(Color &cor, int corInt);
void escurecerCor(Color &corOriginal, Color &cor, float fatorEscurecer);
void desenharSuporte(const Tabuleiro &tabuleiro);
void desenharBaseTabuleiro(const Tabuleiro &tabuleiro);
void desenharPecasTabuleiro(const Tabuleiro &tabuleiro);
void animarPecaTabuleiro(const FilaAcoes &acoes);
Texture2D& carregarTexturaTabuleiro();

void desenharTabuleiro(const Tabuleiro &tabuleiro, Mouse &mouse, const FilaAcoes &acoes) {
    BeginDrawing();

    ClearBackground(GRAY);
    SetMouseCursor(mouse.tipoCursor);
    desenharSuporte(tabuleiro);
    desenharPecasTabuleiro(tabuleiro);
    if (acoes.tam > 0) {
        animarPecaTabuleiro(acoes);
    }
    desenharBaseTabuleiro(tabuleiro);

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
}

void desenharBaseTabuleiro(const Tabuleiro &tabuleiro) {
    Texture2D textura = carregarTexturaTabuleiro();
    int desloca = 5;
    Color cor;

    converterIntParaColor(cor, tabuleiro.corSuporte);
    DrawTextureEx(textura, (Vector2){TABULEIRO_PECAS_TAM_X1 - desloca, TABULEIRO_PECAS_TAM_Y1 - desloca - 1}, 0.0f, 1.0f, cor);
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

void animarPecaTabuleiro(const FilaAcoes &acoes) {
    for (int i = 0; i < acoes.tam; i++) {
        if (acoes.acao[i].concluida) {
            continue;
        }
        Color cor, corEscurecida;
        Vector2 posCentroPeca = {
            acoes.acao[i].animacao.x,
            acoes.acao[i].animacao.y
        };

        converterIntParaColor(cor, acoes.acao[i].autor->cor);
        escurecerCor(cor, corEscurecida, 0.85f);

        DrawCircleV(posCentroPeca, PECAS_RAIO, corEscurecida);
        DrawCircleV(posCentroPeca, PECAS_RAIO - 5, cor);
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
