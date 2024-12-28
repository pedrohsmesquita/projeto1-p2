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
#include "raylib.h"
#include "audio.h"

void telaJogo(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro, Mouse &mouse, bool &janelaAtiva) {
    Jogador *jogadorPtr = definirTurno(jogador1);
    FilaAcoes acoes;
    bool vitoria = false, empateJ = false;

    filaAcoesEstadoInicial(acoes);
    carregarPecasAudio();
    while (janelaAtiva) {
        lerMouse(mouse);
        escolherColuna(tabuleiro, mouse);
        int colunaEscolhida = mouse.estadoEscolhido;
        if (mouse.click && acaoValida(tabuleiro, colunaEscolhida)) {
            int linha = tabuleiro.linhasLivres[colunaEscolhida];
            efetuarAcao(*jogadorPtr, tabuleiro, linha, colunaEscolhida);
            adicionarAcao(acoes, jogadorPtr, linha, colunaEscolhida,
                          tabuleiro.pecasPosicaoXGrid[colunaEscolhida][0] + PECAS_RAIO,
                          -36.0f, tabuleiro.pecasPosicaoYGrid[linha][0] + PECAS_RAIO * 1.1,
                          0.0f, 2500.0f);
            jogadorPtr = trocarTurno(jogador1, jogador2);
        }
        float deltaTempo = GetFrameTime();
        for (int i = 0; i < acoes.tam; i++) {
            if (acoes.acao[i].concluida) {
                continue;
            }
            acoes.acao[i].animacao.v += acoes.acao[i].animacao.a * deltaTempo;
            acoes.acao[i].animacao.y += acoes.acao[i].animacao.v * deltaTempo;
            if (acoes.acao[i].animacao.y > acoes.acao[i].animacao.yf) {
                acoes.acao[i].concluida = true;
                adicionarPeca(tabuleiro, acoes.acao[i].linha, acoes.acao[i].col,
                               acoes.acao[i].autor->id, acoes.acao[i].autor->cor);
                // L�gica vit�ria provis�ria
                if (verificarVitoria(*(acoes.acao[i].autor), tabuleiro, acoes.acao[i].linha, acoes.acao[i].col)) {
                    vitoria = true;
                }
                tocarPecaClick();
            }
        }
        // L�gica empate provis�ria
        if (empate(jogador1, jogador2)) {
            empateJ = true;
        }
        manterMusicaTocando();
        desenharTabuleiro(tabuleiro, mouse, acoes);
        janelaAtiva = !WindowShouldClose() && !vitoria && !empateJ;
    }
    descarregarTexturaTabuleiro();
    descarregarPecasAudio();
}
