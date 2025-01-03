#include "raylib.h"
#include "lig4.h"
#include "mouse.h"
#include "audio.h"
#include "interface.h"
#include "render.h"
#include "arquivo.h"
#include <cstring>

#define JOGAR 0
#define COMO_JOGAR 1
#define CUSTOMIZAR 2
#define SAIR 3

void inicializarMenuInicial(Caixa caixas[], Rectangle caixasRet[], Texto textos[], Texto &nome, Texto &nome4);
void inicializarJogadorTabuleiro(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro);

int main(void)
{
    Tabuleiro tabuleiro;
    Jogador jogador1, jogador2;
    Mouse mouse;
    const Color cores[] = {
        (Color){217, 33, 33, 255},
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        (Color){77, 0, 146, 255},
        (Color){150, 83, 236, 255}
    };
    bool janelaAtiva, mouseSobre = false;
    int selecaoTela, cor = 0;
    float tempoAnterior, tempoAtual;

    // Inicializações do Raylib
    //SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags (FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(LARGURA, ALTURA, "LIG4");
    SetExitKey(0);
    InitAudioDevice();
    SetTargetFPS(60);

    inicializarJogadorTabuleiro(jogador1, jogador2, tabuleiro);
    carregarAudio();
    carregarFonte();

    Caixa caixasTextos[4];
    Rectangle caixaRet[4];
    Texto opcoes[4], nome, nome4;
    inicializarMenuInicial(caixasTextos, caixaRet, opcoes, nome, nome4);
    nome4.cor = cores[0];


    janelaAtiva = !WindowShouldClose();
    selecaoTela = -1;
    tempoAnterior = GetTime();

    tocarMusicaFundo();
    while (janelaAtiva) {
        switch (selecaoTela) {
        case JOGAR:
            telaJogo(jogador1, jogador2, tabuleiro, mouse, janelaAtiva);
            selecaoTela = -1;
            break;
        case COMO_JOGAR:
            // Tela de como jogar aqui.
            break;
        case CUSTOMIZAR:
            telaCustomizar(jogador1, jogador2, tabuleiro, mouse, janelaAtiva);
            selecaoTela = -1;
            break;
        case SAIR:
            janelaAtiva = false;
            break;
        }
        if (janelaAtiva) {
            lerMouse(mouse);
            for (int i = JOGAR; i <= SAIR; i++) {
                if (mouseSobreCaixa(caixasTextos[i], mouse)) {
                    mouse.estadoEscolhido = i;
                    opcoes[i].cor = (Color) {255, 239, 221, 255};
                    if (!mouseSobre) {
                        tocarMouseSobre();
                        mouseSobre = true;
                    }
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        selecaoTela = mouse.estadoEscolhido;
                        tocarBotaoClick();
                    }
                    break;
                } else {
                    opcoes[i].cor = COR_FUNDO;
                }
            }
            if (mouse.estadoEscolhido == -1) {
                mouseSobre = false;
            }
            tempoAtual = GetTime();
            if (tempoAtual - tempoAnterior >= 1.5f) {
                tempoAnterior = tempoAtual;
                cor++;
                if (cor >= 7) {
                    cor = 0;
                }
                nome4.cor = cores[cor];
            }
            BeginDrawing();
            ClearBackground(COR_FUNDO);
            desenharLetraContorno(nome, 7.0f);
            desenharLetraContorno(nome4, 7.0f);
            for (int i = JOGAR; i <= SAIR; i++) {
                //DrawTextEx(opcoes[i].fonte, opcoes[i].conteudo, opcoes[i].posicao, opcoes[i].tamanho, opcoes[i].espacamento, opcoes[i].cor);
                desenharLetraContorno(opcoes[i], 1.0f);
            }
            EndDrawing();
            manterMusicaTocando();
            janelaAtiva = !WindowShouldClose();
        }
    }

    descarregarAudio();
    descarregarFonte();

    return 0;
}

void inicializarMenuInicial(Caixa caixas[], Rectangle caixasRet[], Texto textos[], Texto &nome, Texto &nome4) {
    static char *opcoes[] = {"Jogar", "Como Jogar", "Customizar", "Sair"};
    static Vector2 textoPos[4], nomePos;
    Vector2 temp;

    temp = MeasureTextEx(obterOpenSansSemiBold32(), opcoes[0], 32.0f, 1.0f);
    caixasRet[0] = {
        LARGURA/2 - temp.x/2, ALTURA/2 + 10,
        temp.x, temp.y - 10
    };
    textoPos[0] = {caixasRet[0].x, caixasRet[0].y - 10};
    inicializarCaixa(caixas[0], caixasRet[0], 0.0f, 0, CLITERAL(Color) {0, 0, 0, 0});
    inicializarTexto(textos[0], textoPos[0], opcoes[0], 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());

    for (int i = 1; i < 4; i++) {
        temp = MeasureTextEx(obterOpenSansSemiBold32(), opcoes[i], 32.0f, 1.0f);
        caixasRet[i] = {
            LARGURA/2 - temp.x/2, (caixasRet[i-1].y + caixasRet[i-1].height + 16) + 10,
            temp.x, temp.y - 10
        };
        inicializarCaixa(caixas[i], caixasRet[i], 0.0, 0, caixas[0].cor);
        textoPos[i] = {caixasRet[i].x, caixasRet[i].y - 8};
        inicializarTexto(textos[i], textoPos[i], opcoes[i], 32.0f, 1.0f, textos[0].cor, obterOpenSansSemiBold32());
    }
    temp = MeasureTextEx(obterBoogaloo192(), "LIG4", 192.0f, 1.0f);
    nomePos = {(LARGURA - temp.x)/2, (ALTURA - temp.y)/8};
    inicializarTexto(nome, nomePos, "LIG", 192.0f, 1.0f, textos[0].cor, obterBoogaloo192());
    const float y = nomePos.y;
    temp = MeasureTextEx(obterBoogaloo256(), "4", 256.0f, 0.0f);
    nomePos = {(LARGURA - temp.x)/2 + temp.x - 14, y - (temp.y - y)/5};
    inicializarTexto(nome4, nomePos, "4", 256.0f, 0.0f, textos[0].cor, obterBoogaloo256());
}

void inicializarJogadorTabuleiro(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro) {
    Color cor[3];
    char nomes[2][13];

    if (!carregarCustomizacao(cor, nomes)) {
        cor[0] = BLUE;
        cor[1] = YELLOW;
        cor[2] = RED;
        strcpy(nomes[0], "Jogador 1");
        strcpy(nomes[1], "Jogador 2");
        salvarCustomizacao(cor, nomes);
    }
    jogadorEstadoInicial(jogador1, 1, cor[0], nomes[0]);
    jogadorEstadoInicial(jogador2, 2, cor[1], nomes[1]);
    tabuleiroEstadoInicial(tabuleiro, cor[2]);
}
