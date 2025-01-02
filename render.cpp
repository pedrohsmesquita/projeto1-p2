/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "render.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "render.h".
 */
#include "render.h"
#include "raylib.h"

//void converterIntParaColor(Color &cor, int corInt);
void escurecerCor(const Color &corOriginal, Color &cor, float fatorEscurecer);
void desenharSuporte(const Tabuleiro &tabuleiro);
void desenharBaseTabuleiro(const Tabuleiro &tabuleiro);
void desenharPecasTabuleiro(const Tabuleiro &tabuleiro);
Texturas& obterTexturas();
bool igualdadeCor(const Color &cor1, const Color &cor2);

void desenharTabuleiro(const Tabuleiro &tabuleiro, const Mouse &mouse) {
    ClearBackground(COR_FUNDO);
    SetMouseCursor(mouse.tipoCursor);
    desenharSuporte(tabuleiro);
    desenharPecasTabuleiro(tabuleiro);
    desenharBaseTabuleiro(tabuleiro);
}

/*
void converterIntParaColor(Color &cor, int corInt) {
    cor.r = 0xFF & (corInt >> 24);
    cor.g = 0xFF & (corInt >> 16);
    cor.b = 0xFF & (corInt >> 8);
    cor.a = 0xFF & corInt;
}
*/

void escurecerCor(const Color &corOriginal, Color &cor, float fatorEscurecer) {
    cor.r = corOriginal.r * fatorEscurecer;
    cor.g = corOriginal.g * fatorEscurecer;
    cor.b = corOriginal.b * fatorEscurecer;
    cor.a = corOriginal.a;
}

void desenharSuporte(const Tabuleiro &tabuleiro) {
    int deslocar = 5;
    Rectangle partePeca, partePecaSombra, pilarEsq, pilarDir;
    //Color sombra;

    pilarEsq = {
        0, TABULEIRO_DESLOCAY,
        TABULEIRO_DESLOCAX - deslocar, 768 - 90
    };
    pilarDir = {
        TABULEIRO_PECAS_TAM_X2 + deslocar, TABULEIRO_DESLOCAY,
        TABULEIRO_DESLOCAX, 768 - 90
    };
    //escurecerCor(tabuleiro.corSuporte, sombra, 0.9f);

    DrawRectangleRounded(pilarEsq, 0.35f, 0, tabuleiro.corSuporte);
    DrawRectangleRounded(pilarDir, 0.35f, 0, tabuleiro.corSuporte);
}

void desenharBaseTabuleiro(const Tabuleiro &tabuleiro) {
    static const Texturas& texturas = obterTexturas();
    int desloca = 5;

    DrawTextureEx(texturas.tabuleiro, (Vector2){TABULEIRO_PECAS_TAM_X1 - desloca, TABULEIRO_PECAS_TAM_Y1 - desloca - 1}, 0.0f, 1.0f, tabuleiro.corSuporte);
}

void desenharPecasTabuleiro(const Tabuleiro &tabuleiro) {
    const float escurecer = 0.85f;
    const Color fundo = COR_FUNDO;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            Color corEscurecida;
            if (igualdadeCor(tabuleiro.grid[i][j].corPeca, fundo)) {
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO, tabuleiro.grid[i][j].corPeca);
            } else {
                escurecerCor(tabuleiro.grid[i][j].corPeca, corEscurecida, escurecer);
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO + 1, corEscurecida);
                DrawCircleV(tabuleiro.grid[i][j].posicao, PECAS_RAIO - 5, tabuleiro.grid[i][j].corPeca);
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

void desenharPerfil(const Jogador &jogador, float y) {
    Rectangle retanguloEx = {
        850.0f, y,
        169.0f, 150.0f
    };
    Rectangle retanguloIn = {
        retanguloEx.x + 5, retanguloEx.y + 5,
        retanguloEx.width - 10, retanguloEx.height - 10
    };
    Vector2 circuloCentro = {
        retanguloIn.x + retanguloIn.width/2, retanguloIn.y + 28
    };
    Vector2 temp = MeasureTextEx(obterOpenSansSemiBold16(), jogador.nome, 16.0f, 1.0f);
    Vector2 nomePosicao = {
        retanguloIn.x + 2 + (retanguloIn.width - temp.x)/2, circuloCentro.y + 30
    };
    Vector2 pecaPosicao = {
        retanguloIn.x + 5, nomePosicao.y + 25
    };
    Vector2 turnoPosicao = {
        retanguloIn.x + 5, pecaPosicao.y + 25
    };
    Color cor = COR_FUNDO, corEscurecida;

    escurecerCor(jogador.cor, corEscurecida, 0.85f);
    if (jogador.vencedor) {
        cor.r = 255;
        cor.g = 220;
        cor.b = 115;
    }
    DrawRectangleRounded(retanguloEx, 0.15f, 0, cor);
    DrawRectangleRoundedLines(retanguloEx, 0.15f, 0, BLACK);
    DrawRectangleRoundedLines(retanguloIn, 0.15f, 0, BLACK);
    DrawCircleV(circuloCentro, 25, corEscurecida);
    DrawCircleV(circuloCentro, 21, jogador.cor);
    DrawTextEx(obterOpenSansSemiBold16(), jogador.nome, nomePosicao, 16.0f, 1.0f, BLACK);
    DrawTextEx(obterOpenSansSemiBold16(), TextFormat("Pecas: %d", jogador.pecas), pecaPosicao, 16.0f, 1.0f, BLACK);
    if (jogador.turno) {
        DrawTextEx(obterOpenSansSemiBold16(), "Jogando", turnoPosicao, 16.0f, 1.0f, BLACK);
    } else {
        DrawTextEx(obterOpenSansSemiBold16(), "Esperando", turnoPosicao, 16.0f, 1.0f, BLACK);
    }
}

void desenharBotao(const Caixa &caixa, const Texto &texto) {
    Color corEscurecida;

    escurecerCor(caixa.cor, corEscurecida, 0.80f);
    DrawRectangleRounded(caixa.retangulo, caixa.redondeza, caixa.segmentos, caixa.cor);
    DrawRectangleRoundedLines(caixa.retangulo, caixa.redondeza, caixa.segmentos, corEscurecida);
    DrawTextEx(texto.fonte, texto.conteudo, texto.posicao, texto.tamanho, texto.espacamento, texto.cor);
}

void carregarTexturaTabuleiro() {
    Texturas& texturas = obterTexturas();

    texturas.tabuleiro = LoadTexture("assets/images/base.png");
}

void descarregarTexturaTabuleiro() {
    Texturas& texturas = obterTexturas();

    UnloadTexture(texturas.tabuleiro);
}

bool igualdadeCor(const Color &cor1, const Color &cor2) {
    return cor1.r == cor2.r && cor1.g == cor2.g & cor1.b == cor2.b;
}

Texturas& obterTexturas() {
    static Texturas texturas;

    return texturas;
}
