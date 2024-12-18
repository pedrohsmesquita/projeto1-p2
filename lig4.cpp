/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "lig4.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "lig4.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis por coordenar o fluxo do programa, isto �, ir� unir
 * todos os componentes relacionados a uma parte espec�fica do programa (tela
 * inicial, customiza��o, regras, jogo) e garantir seu funcionamento.
 *
 * Em outras palavras, unir a l�gica do programa (obten��o de entradas, mudar
 * estados internos, etc) � apresenta��o gr�fica ao usu�rio (UI).
 */
#include "lig4.h"
#include "jogo.h"
#include "render.h"
#include <raylib.h>

void telaJogo(Jogador &jogador, Tabuleiro &tabuleiro, Mouse &mouse, bool &janelaAtiva) {
    while (janelaAtiva) {
        lerMouse(mouse);
        escolherColuna(tabuleiro, mouse);
        int colunaEscolhida = obterMouseEstado(mouse);
        if (acaoValida(tabuleiro, colunaEscolhida)) {
            efetuarAcao(jogador, tabuleiro, colunaEscolhida);
        }
        desenharTabuleiro(tabuleiro, mouse);
        janelaAtiva = !WindowShouldClose();
    }
}
