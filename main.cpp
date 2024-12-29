#include "raylib.h"
#include "lig4.h"
#include "mouse.h"
#include "audio.h"

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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 768, "LIG4");
    InitAudioDevice();
    SetTargetFPS(60);

    carregaAudio();
    tabuleiroEstadoInicial(tabuleiro, ColorToInt(COR_FUNDO), ColorToInt(RED));
    jogadorEstadoInicial(jogador1, 1, 21, ColorToInt(BLUE), "Jogador 1");
    jogadorEstadoInicial(jogador2, 2, 21, ColorToInt(YELLOW), "Jogador 2");


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

    return 0;
}
