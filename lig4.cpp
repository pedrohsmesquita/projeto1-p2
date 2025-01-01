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
    Vector2 centrosVPiPf[3];

    carregarAudioJogo();
    while (janelaAtiva) {
        lerMouse(mouse);
        escolherColuna(tabuleiro, mouse);
        int colunaEscolhida = mouse.estadoEscolhido;
        if (mouse.click && acaoValida(tabuleiro, colunaEscolhida)) {
            int linha = tabuleiro.linhasLivres[colunaEscolhida];
            efetuarAcao(*jogadorPtr, tabuleiro, linha, colunaEscolhida);
            jogadorPtr = trocarTurno(jogador1, jogador2);
        }
        float deltaTempo = GetFrameTime();
        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                if (tabuleiro.grid[i][j].animando == false) {
                    continue;
                }
                atualizarPosicaoPeca(tabuleiro.grid[i][j], deltaTempo);
                float yf = tabuleiro.pecasPosicaoYGrid[i][0] + PECAS_RAIO;
                if (tabuleiro.grid[i][j].posicao.y > yf) {
                    consumarAcao(tabuleiro.grid[i][j], jogador1, jogador2, yf);
                    if (verificarVitoria(tabuleiro, i, j, centrosVPiPf)) {
                        tabuleiro.estado.vitoria = true;
                        jogadorPtr = obterVencedor(tabuleiro.grid[i][j], jogador1, jogador2);
                        jogadorPtr->vencedor = true;
                    }
                    tocarPecaClick();
                }
            }
        }
        // L�gica empate provis�ria
        if (empate(jogador1, jogador2)) {
            tabuleiro.estado.empate = true;
        }
        if (tabuleiro.estado.vitoria) {
            tocarVitoria();
            break;
        }

        manterMusicaTocando();
        BeginDrawing();
        desenharTabuleiro(tabuleiro, mouse);
        desenharPerfil(jogador1, 150);
        desenharPerfil(jogador2, 468);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
    if (tabuleiro.estado.vitoria) {
        float linhaProgresso = 0.0f;

        while (janelaAtiva) {
            lerMouse(mouse);
            if (linhaProgresso < 1.0f) {
                calcularLinhaVitoria(centrosVPiPf, linhaProgresso);
            }

            BeginDrawing();
            desenharTabuleiro(tabuleiro, mouse);
            desenharPerfil(jogador1, 150);
            desenharPerfil(jogador2, 468);
            linhaVitoria(centrosVPiPf);
            EndDrawing();
            janelaAtiva = !WindowShouldClose();
        }
    }
    janelaAtiva = false;
    descarregarTexturaTabuleiro();
    descarregarAudioJogo();
}
