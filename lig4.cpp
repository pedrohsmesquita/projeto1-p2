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

void telaJogo(Jogador &jogador, Tabuleiro &tabuleiro, bool &janelaAtiva) {
    int colunaEscolhida;

    while (janelaAtiva) {
        colunaEscolhida = escolherColuna(tabuleiro);
        if (colunaEscolhida >= 0 && obterLinhaLivre(tabuleiro, colunaEscolhida) >= 0) {
            efetuarAcao(jogador, tabuleiro, colunaEscolhida);
        }
        desenharTabuleiro(tabuleiro);
        janelaAtiva = !WindowShouldClose();
    }
}
