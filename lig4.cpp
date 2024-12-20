/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "lig4.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "lig4.h". Todas as funções desse arquivo
 * deverão ser responsáveis por coordenar o fluxo do programa, isto é, irá unir
 * todos os componentes relacionados a uma parte específica do programa (tela
 * inicial, customização, regras, jogo) e garantir seu funcionamento.
 *
 * Em outras palavras, unir a lógica do programa (obtenção de entradas, mudar
 * estados internos, etc) à apresentação gráfica ao usuário (UI).
 */
#include "lig4.h"
#include "jogo.h"
#include "render.h"
#include <raylib.h>

void telaJogo(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro, Mouse &mouse, bool &janelaAtiva) {
    Jogador *jogadorPtr = definirTurno(jogador1);
    while (janelaAtiva) {
        // Lógica empate provisória
        if (empate(jogador1, jogador2)) {
            janelaAtiva = 0;
            break;
        }
        lerMouse(mouse);
        escolherColuna(tabuleiro, mouse);
        int colunaEscolhida = obterMouseEstado(mouse);
        if (acaoValida(tabuleiro, colunaEscolhida)) {
            int linha = obterLinhaLivre(tabuleiro, colunaEscolhida);
            efetuarAcao(*jogadorPtr, tabuleiro, linha, colunaEscolhida);
            // Lógica vitória provisória
            if (verificarVitoria(*jogadorPtr, tabuleiro, linha, colunaEscolhida)) {
                janelaAtiva = 0;
                break;
            }
            jogadorPtr = trocarTurno(jogador1, jogador2);
        }
        desenharTabuleiro(tabuleiro, mouse);
        janelaAtiva = !WindowShouldClose();
    }
}
