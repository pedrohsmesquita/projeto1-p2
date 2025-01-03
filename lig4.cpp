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
#include "menu.h"

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
                        if (empate(jogador1, jogador2)) {
                            tabuleiro.estado.empate = true;
                        }
                        tocarPecaClick();
                    }
                }
            }
            if (tabuleiro.estado.vitoria) {
                tocarVitoria();
                break;
            }
            if (tabuleiro.estado.empate) {
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
            Color corMouseSobre;
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

            corMouseSobre = CLITERAL(Color) {255, 246, 236, 255};
            /*
            botaoCor = COR_FUNDO;
            botaoCor = CLITERAL(Color) {255, 246, 236, 255};
            textoCor = COR_FUNDO;
            textoCorMouse = botaoCorMouse;
            textoCorMouse = textoCor;
            */

            inicializarCaixa(botaoVoltar, voltarRet, 0.75f, 10, COR_FUNDO);
            inicializarCaixa(botaoJogarNovamente, jogarNovamenteRet, 0.75f, 10, COR_FUNDO);

            temp = MeasureTextEx(obterOpenSansSemiBold32(), "Voltar", 32.0f, 1.0f);
            centralizar = {
                voltarRet.x + (voltarRet.width - temp.x)/2,
                voltarRet.y + (voltarRet.height - temp.y)/2
            };
            inicializarTexto(voltarText, centralizar, "Voltar", 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());

            temp = MeasureTextEx(obterOpenSansSemiBold32(), "Continuar", 32.0f, 1.0f);
            centralizar = {
                jogarNovamenteRet.x + (jogarNovamenteRet.width - temp.x)/2,
                jogarNovamenteRet.y + (jogarNovamenteRet.height - temp.y)/2
            };
            inicializarTexto(jogarNovamenteText, centralizar, "Continuar", 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());

            while (janelaAtiva) {
                lerMouse(mouse);
                if (tabuleiro.estado.vitoria && linhaProgresso < 1.0f) {
                    calcularLinhaVitoria(centrosVPiPf, linhaProgresso);
                }
                if (mouseSobreCaixa(botaoJogarNovamente, mouse)) {
                    botaoJogarNovamente.cor = corMouseSobre;
                    jogarNovamenteText.cor = corMouseSobre;
                    if (!mouseSobreJogar) {
                        tocarMouseSobre();
                        mouseSobreJogar = true;
                    }
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        tocarBotaoClick();
                        break;
                    }
                } else {
                    botaoJogarNovamente.cor = COR_FUNDO;
                    jogarNovamenteText.cor = COR_FUNDO;
                    mouseSobreJogar = false;
                }
                if (mouseSobreCaixa(botaoVoltar, mouse)) {
                    botaoVoltar.cor = corMouseSobre;
                    voltarText.cor = corMouseSobre;
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
                    botaoVoltar.cor = COR_FUNDO;
                    voltarText.cor = COR_FUNDO;
                    mouseSobreVoltar = false;
                }

                BeginDrawing();
                desenharTabuleiro(tabuleiro, mouse);
                desenharPerfil(jogador1, 150.0f);
                desenharPerfil(jogador2, 468.0f);
                if (tabuleiro.estado.vitoria) {
                    linhaVitoria(centrosVPiPf);
                }
                desenharBotao(botaoJogarNovamente, jogarNovamenteText, 1.0f, 0.5f);
                desenharBotao(botaoVoltar, voltarText, 1.0f, 0.5f);
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

void telaCustomizar(Jogador &jogador1, Jogador &jogador2, Tabuleiro &tabuleiro, Mouse &mouse, bool &janelaAtiva) {
    Rectangle textosRet[3], botoesRet[2], quadro, quadroCustomizar, deslizantes[3], barra[3];
    Caixa caixas[3], botoes[2];
    Texto textos[3], botoesTexto[2];
    Color cores[3];
    bool mouseSobre[3] = {false, false, false};
    bool opcaoSelecionada[3] = {false, false, false}, selecionado = false;
    int escolha, escolhido = -1;

    quadro = {
        LARGURA/8.0f - 100.0f, ALTURA/2.0f - 150.0f,
        200.0f, 300.0f
    };
    quadroCustomizar = {
        LARGURA/4.0f, 68.0f,
        LARGURA - LARGURA/4.0 - 25.0f, ALTURA - 136.0f
    };

    inicializarOpcaoCustomizar(quadro, caixas, textosRet, textos, jogador1, jogador2);
    inicializarQuadroCustomizar(quadroCustomizar, barra, deslizantes);
    inicializarBotoesCustomizar(quadro, botoes, botoesRet, botoesTexto);

    cores[0] = jogador1.cor;
    cores[1] = jogador2.cor;
    cores[2] = tabuleiro.corSuporte;

    carregarTexturaTabuleiro();
    while (janelaAtiva) {
        lerMouse(mouse);
        selecionarOpcaoCustomizar(caixas, mouse, opcaoSelecionada, mouseSobre, selecionado);
        escolha = mouse.estadoEscolhido;
        if (IsKeyDown(KEY_ESCAPE)) {
            selecionado = false;
            opcaoSelecionada[escolhido] = false;
        }
        if (escolha != -1 && escolha != escolhido) {
            escolhido = escolha;
            deslizantesAtualizarBarra(deslizantes, cores[escolhido]);
        }
        if (selecionado) {
            for (int i = 0 ; i < 3; i++) {
                if (mouseSobreDeslizante(barra[i], deslizantes[i], mouse)) {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                        deslizantes[i].x = mouse.x;
                        if (deslizantes[i].x < barra[i].x) {
                            deslizantes[i].x = barra[i].x;
                        } else if (deslizantes[i].x > barra[i].x + barra[i].width) {
                            deslizantes[i].x = barra[i].x + barra[i].width;
                        }
                    }
                    break;
                }
            }
        }
        if (escolhido >= 0) {
            atualizarCorDeslizantes(deslizantes, cores[escolhido]);
        }

        manterMusicaTocando();
        BeginDrawing();
        ClearBackground(COR_FUNDO);
        DrawRectangleRoundedLines(quadro, 0.10f, 0, BLACK);
        for (int i = 0; i < 3; i++) {
            desenharBotao(caixas[i], textos[i], 1.0f, 1.0f);
        }
        if (selecionado) {
            desenharQuadroCustomizar(quadroCustomizar, barra, deslizantes);
            if (escolhido == 2) {
                desenharTabuleiroCustomizar(quadroCustomizar, cores[escolhido]);
            } else {
                desenharPecaGigante(quadroCustomizar, cores[escolhido]);
            }
        }
        desenharBotao(botoes[0], botoesTexto[0], 1.0f, 0.0f);
        desenharBotao(botoes[1], botoesTexto[1], 1.0f, 0.0f);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
    descarregarTexturaTabuleiro();
}
