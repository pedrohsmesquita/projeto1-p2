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
#include "raylib.h"
#include "audio.h"

void telaJogo(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro, Mouse &mouse, bool &janelaAtiva) {
    Jogador *jogadorPtr = definirTurno(jogador1);
    Vector2 centrosVPiPf[3];
    bool jogar = true;

    carregarAudioJogo();
    carregarTexturaTabuleiro();
    while (jogar) {
        resetarGrid(tabuleiro);
        resetarJogador(jogador1);
        resetarJogador(jogador2);
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
            if (tabuleiro.estado.vitoria) {
                tocarVitoria();
                break;
            }
            if (empate(jogador1, jogador2)) {
                tabuleiro.estado.empate = true;
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
        if (tabuleiro.estado.vitoria || tabuleiro.estado.empate) {
            float linhaProgresso = 0.0f;
            bool mouseSobreJogar = false, mouseSobreVoltar = false;
            Caixa botaoVoltar, botaoJogarNovamente;
            Color botaoCor, botaoCorMouse, textoCor, textoCorMouse;
            Rectangle jogarNovamenteRet = {
                850.0f, 326.0f,
                169.0f, 40.0f
            };
            Rectangle voltarRet = {
                850.0f, 402.0f,
                169.0f, 40.0f
            };
            Vector2 temp, centralizar;
            Texto voltarText, jogarNovamenteText;

            //botaoCor = CLITERAL(Color) {255, 246, 236, 255};
            botaoCor = COR_FUNDO;
            botaoCorMouse = CLITERAL(Color) {255, 246, 236, 255};
            textoCor = CLITERAL(Color) {169, 169, 169, 255};
            textoCorMouse = CLITERAL(Color) {208, 208, 208, 255};

            inicializarCaixa(botaoVoltar, voltarRet, 0.75f, 10, botaoCor);
            inicializarCaixa(botaoJogarNovamente, jogarNovamenteRet, 0.75f, 10, botaoCor);

            temp = MeasureTextEx(obterOpenSansSemiBold32(), "Voltar", 32.0f, 1.0f);
            centralizar = {
                voltarRet.x + (voltarRet.width - temp.x)/2,
                voltarRet.y + (voltarRet.height - temp.y)/2
            };
            inicializarTexto(voltarText, centralizar, "Voltar", 32.0f, 1.0f, textoCor, obterOpenSansSemiBold32());

            temp = MeasureTextEx(obterOpenSansSemiBold32(), "Continuar", 32.0f, 1.0f);
            centralizar = {
                jogarNovamenteRet.x + (jogarNovamenteRet.width - temp.x)/2,
                jogarNovamenteRet.y + (jogarNovamenteRet.height - temp.y)/2
            };
            inicializarTexto(jogarNovamenteText, centralizar, "Continuar", 32.0f, 1.0f, textoCor, obterOpenSansSemiBold32());

            while (janelaAtiva) {
                lerMouse(mouse);
                if (tabuleiro.estado.vitoria && linhaProgresso < 1.0f) {
                    calcularLinhaVitoria(centrosVPiPf, linhaProgresso);
                }
                if (mouseSobreCaixa(botaoJogarNovamente, mouse)) {
                    botaoJogarNovamente.cor = botaoCorMouse;
                    jogarNovamenteText.cor = textoCorMouse;
                    if (!mouseSobreJogar) {
                        tocarMouseSobre();
                        mouseSobreJogar = true;
                    }
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        tocarBotaoClick();
                        break;
                    }
                } else {
                    botaoJogarNovamente.cor = botaoCor;
                    jogarNovamenteText.cor = textoCor;
                    mouseSobreJogar = false;
                }
                if (mouseSobreCaixa(botaoVoltar, mouse)) {
                    botaoVoltar.cor = botaoCorMouse;
                    voltarText.cor = textoCorMouse;
                    if (!mouseSobreVoltar) {
                        tocarMouseSobre();
                        mouseSobreVoltar = true;;
                    }
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogar = false;
                        tocarBotaoClick();
                        break;
                    }
                } else {
                    botaoVoltar.cor = botaoCor;
                    voltarText.cor = textoCor;
                    mouseSobreVoltar = false;
                }

                BeginDrawing();
                desenharTabuleiro(tabuleiro, mouse);
                desenharPerfil(jogador1, 150.0f);
                desenharPerfil(jogador2, 468.0f);
                if (tabuleiro.estado.vitoria) {
                    linhaVitoria(centrosVPiPf);
                }
                desenharBotao(botaoJogarNovamente, jogarNovamenteText);
                desenharBotao(botaoVoltar, voltarText);
                EndDrawing();
                janelaAtiva = !WindowShouldClose();
            }
        }
        if (!janelaAtiva) {
            break;
        }
        if (jogar) {
            if (jogador1.turno) {
                jogadorPtr = &jogador1;
            } else {
                jogadorPtr = &jogador2;
            }
        } else {
            jogador1.turno = false;
            jogador2.turno = false;
        }
    }
    descarregarTexturaTabuleiro();
    descarregarAudioJogo();
}
