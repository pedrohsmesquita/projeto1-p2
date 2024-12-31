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
void linhaVitoria(const Vector2 centro[]);
bool igualdadeCor(const Color &cor1, const Color &cor2);
Texture2D& carregarTexturaTabuleiro();

void desenharTabuleiro(const Tabuleiro &tabuleiro, Mouse &mouse, const Vector2 centro[]) {
    ClearBackground(COR_FUNDO);
    SetMouseCursor(mouse.tipoCursor);
    desenharSuporte(tabuleiro);
    desenharPecasTabuleiro(tabuleiro);
    desenharBaseTabuleiro(tabuleiro);
    if (tabuleiro.estado.vitoria) {
        linhaVitoria(centro);
    }
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
    static const Texture2D textura = carregarTexturaTabuleiro();
    int desloca = 5;
    Color cor;

    converterIntParaColor(cor, tabuleiro.corSuporte);
    DrawTextureEx(textura, (Vector2){TABULEIRO_PECAS_TAM_X1 - desloca, TABULEIRO_PECAS_TAM_Y1 - desloca - 1}, 0.0f, 1.0f, cor);
}

void desenharPecasTabuleiro(const Tabuleiro &tabuleiro) {
    const float escurecer = 0.85f;
    const Color fundo = COR_FUNDO;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            Color cor, corEscurecida;
            converterIntParaColor(cor, tabuleiro.grid[i][j].corPeca);
            if (igualdadeCor(cor, fundo)) {
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO, cor);
            } else {
                escurecerCor(cor, corEscurecida, escurecer);
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO + 1, corEscurecida);
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO - 5, cor);
            }
        }
    }
}

void linhaVitoria(const Vector2 centro[]) {
    Color corBorda, cor;

    cor = WHITE;
    escurecerCor(cor, corBorda, 0.75f);
    DrawLineEx(centro[0], centro[2], 5.0f, corBorda);
    DrawLineEx(centro[0], centro[2], 2.0f, cor);
}

Texture2D& carregarTexturaTabuleiro() {
    static Texture2D textura = LoadTexture("assets/images/base.png");

    return textura;
}

void descarregarTexturaTabuleiro() {
    Texture2D& textura = carregarTexturaTabuleiro();

    UnloadTexture(textura);
}

bool igualdadeCor(const Color &cor1, const Color &cor2) {
    return cor1.r == cor2.r && cor1.g == cor2.g & cor1.b == cor2.b;
}
