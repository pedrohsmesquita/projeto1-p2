#include <raylib.h>
#include "lig4.h"
#include "mouse.h"

#define JOGAR 0
#define CUSTOMIZAR 1
#define SAIR 2

int main(void)
{
    Tabuleiro tabuleiro;
    Jogador jogador;
    Mouse mouse;
    bool janelaAtiva;
    int selecaoTela;

    tabuleiroEstadoInicial(tabuleiro, ColorToInt(GRAY), ColorToInt(RED));
    jogadorEstadoInicial(jogador, 1, 21, ColorToInt(BLUE), "Jogador 1");
    InitWindow(1024, 768, "LIG4");
    SetTargetFPS(60);

    janelaAtiva = !WindowShouldClose();
    // Nenhuma l�gica feita para sele��o. Jogo inicia automaticamente.
    selecaoTela = 0;
    while (janelaAtiva) {
        switch (selecaoTela) {
        case 0:
            telaJogo(jogador, tabuleiro, mouse, janelaAtiva);
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

    return 0;
}
