#include "raylib.h"
#include "lig4.h"
#include "mouse.h"
#include "audio.h"
#include "interface.h"

#define JOGAR 0
#define CUSTOMIZAR 1
#define SAIR 2

int main(void)
{
    Tabuleiro tabuleiro;
    Jogador jogador1, jogador2;
    Mouse mouse;
    bool janelaAtiva;
    int selecaoTela;

    // Inicializa��es do Raylib
    //SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags (FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1024, 768, "LIG4");
    InitAudioDevice();
    SetTargetFPS(60);

    carregarAudio();
    carregarFonte();
    tabuleiroEstadoInicial(tabuleiro, RED);
    jogadorEstadoInicial(jogador1, 1, BLUE, "WWWWWWWWWWWW");
    jogadorEstadoInicial(jogador2, 2, YELLOW, "Jogador 2");


    janelaAtiva = !WindowShouldClose();
    // Nenhuma l�gica feita para sele��o. Jogo inicia automaticamente.
    selecaoTela = 0;
    tocarMusicaFundo();
    while (janelaAtiva) {
        switch (selecaoTela) {
        case 0:
            telaJogo(jogador1, jogador2, tabuleiro, mouse, janelaAtiva);
            break;
        case 1:
            // Tela de customiza��o aqui.
            break;
        case 2:
            // Botao sair aqui.
            break;
        default:
            // Nada acontece.
            break;
        }
    }

    descarregarAudio();
    descarregarFonte();

    return 0;
}
