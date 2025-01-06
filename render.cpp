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
        cor.g = 239;
        cor.b = 221;
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

void desenharBotao(const Caixa &caixa, const Texto &texto, float grossura, float escurecer) {
    Color corEscurecida;

    escurecerCor(caixa.cor, corEscurecida, escurecer);
    DrawRectangleRounded(caixa.retangulo, caixa.redondeza, caixa.segmentos, caixa.cor);
    DrawRectangleRoundedLines(caixa.retangulo, caixa.redondeza, caixa.segmentos, corEscurecida);
    desenharLetraContorno(texto, grossura);
}

void desenharLetraContorno(const Texto& texto, float grossura) {

    if (grossura > 0.0f) {
        Color corEscurecida;
        escurecerCor(texto.cor, corEscurecida, 0.70f);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y - grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x - grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
        DrawTextEx(texto.fonte, texto.conteudo,
                   (Vector2){texto.posicao.x + grossura, texto.posicao.y + grossura},
                   texto.tamanho, texto.espacamento, corEscurecida);
    }
    DrawTextEx(texto.fonte, texto.conteudo, texto.posicao, texto.tamanho, texto.espacamento, texto.cor);

}

void desenharQuadroCustomizar(const Rectangle &retangulo, const Rectangle barra[], const Rectangle deslizantes[]) {
    Vector2 r, g, b, tam;

    r = {(barra[0].x + retangulo.x)/2.0f - 10.0f, barra[0].y - 7.0f};
    g = {r.x, barra[1].y - 7.0f};
    b = {r.x, barra[2].y - 7.0f};
    tam = {20.0f, 20.0f};

    DrawRectangleRoundedLines(retangulo, 0.10f, 0.0f, BLACK);
    DrawRectangleV(r, tam, RED);
    DrawRectangleV(g, tam, GREEN);
    DrawRectangleV(b, tam, BLUE);
    for(int i = 0; i < 3; i++) {
        DrawRectangleRounded(barra[i], 0.0f, 0, BLACK);
        DrawRectangleRounded(deslizantes[i], 0.0f, 0, BLACK);
    }
}

void desenharPecaGigante(const Rectangle &retangulo, const Color &cor) {
    Vector2 centro = {
        retangulo.x + retangulo.width/2.0f,
        retangulo.y + retangulo.height/2 - 150.0f
    };
    Color corEscurecida;
    float raio = retangulo.height/8 + 50.0f;

    escurecerCor(cor, corEscurecida, 0.85f);
    DrawCircleV(centro, raio, corEscurecida);
    DrawCircleV(centro, raio - 10.0f, cor);
}

void desenharTabuleiroCustomizar(const Rectangle &quadroCustomizar, const Color &cor) {
    Texturas& texturas = obterTexturas();
    Vector2 pos = {
        quadroCustomizar.x + quadroCustomizar.width/4,
        quadroCustomizar.y + 32.0f
    };

    DrawTextureEx(texturas.tabuleiro, pos, 0.0f, 0.5f, cor);
}

void desenharComoJogar() {
    Vector2 pos, temp;
    Rectangle ret = {
        64.0f, 48.0f,
        LARGURA - 128.0f, ALTURA - 96.0f
    };

    DrawRectangleRoundedLines(ret, 0.10f, 0, BLACK);
    temp = MeasureTextEx(obterOpenSansSemiBold64(), "Como Jogar?", 64.0f, 1.0f);
    pos = {
        ret.x + (ret.width - temp.x)/2.0f,
        ret.y + 12.0f
    };
    DrawTextEx(obterOpenSansSemiBold64(), "Como Jogar?", pos, 64.0f, 1.0f, BLACK);
    pos = {
        ret.x + 12.0f, ret.y + temp.y + 64.0f
    };
    DrawTextEx(obterOpenSansSemiBold32(), "- Utilizando o mouse, selecione uma das colunas para efetuar uma jogada.", pos, 32.0f, 1.0f, BLACK);
    pos = {pos.x, pos.y + 64.0f};
    DrawTextEx(obterOpenSansSemiBold32(), "- Cada jogador realiza uma unica jogada por turno.", pos, 32.0f, 1.0f, BLACK);
    pos = {pos.x, pos.y + 64.0f};
    DrawTextEx(obterOpenSansSemiBold32(), "- Para vencer, forme uma sequencia de 4 cores ou na horizontal ou na\nvertical ou na diagonal.", pos, 32.0f, 1.0f, BLACK);
    pos = {pos.x, pos.y + 128.0f};
    DrawTextEx(obterOpenSansSemiBold32(), "Divirta-se!", pos, 32.0f, 1.0f, BLACK);
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
