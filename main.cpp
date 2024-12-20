#include <raylib.h>
#include "lig4.h"
#include "mouse.h"

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

    tabuleiroEstadoInicial(tabuleiro, ColorToInt(GRAY), ColorToInt(RED));
    jogadorEstadoInicial(jogador1, 1, 21, ColorToInt(BLUE), "Jogador 1");
    jogadorEstadoInicial(jogador2, 2, 21, ColorToInt(YELLOW), "Jogador 2");
    InitWindow(1024, 768, "LIG4");
    SetTargetFPS(60);

    janelaAtiva = !WindowShouldClose();
    // Nenhuma lógica feita para seleção. Jogo inicia automaticamente.
    selecaoTela = 0;
    while (janelaAtiva) {
        switch (selecaoTela) {
        case 0:
            telaJogo(jogador1, jogador2, tabuleiro, mouse, janelaAtiva);
            break;
        case 1:
            // Tela de customização aqui.
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
