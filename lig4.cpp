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
#include "menu.h"
#include "arquivo.h"
#include <cstring>

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

            corMouseSobre = {255, 246, 236, 255};

            inicializarCaixa(botaoVoltar, voltarRet, 0.25f, 10, COR_FUNDO);
            inicializarCaixa(botaoJogarNovamente, jogarNovamenteRet, 0.25f, 10, COR_FUNDO);

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
    Rectangle textosRet[3], botoesRet[2], quadro, quadroCustomizar, deslizantes[3], barra[3], nomeRet;
    Caixa caixas[3], botoes[2], nomeCaixa;
    Texto textos[3], botoesTexto[2], nomeTexto;
    Color cores[3], sobreBotaoCor;
    Vector2 nomePos;
    char nomes[2][NOME_TAM+1];
    bool mouseSobre[3] = {false, false, false}, sobreBotao = false, falha = false;
    bool opcaoSelecionada[3] = {false, false, false}, selecionado = false, sucesso = false;
    int escolha, escolhido = -1, botaoSobre = -1, tamNome;

    quadro = {
        LARGURA/8.0f - 100.0f, ALTURA/2.0f - 150.0f,
        200.0f, 300.0f
    };
    quadroCustomizar = {
        LARGURA/4.0f, 68.0f,
        LARGURA - LARGURA/4.0 - 25.0f, ALTURA - 136.0f
    };

    strncpy(nomes[0], jogador1.nome, NOME_TAM);
    strncpy(nomes[1], jogador2.nome, NOME_TAM);
    nomes[0][NOME_TAM] = '\0';
    nomes[1][NOME_TAM] = '\0';

    inicializarOpcaoCustomizar(quadro, caixas, textosRet, textos, nomes[0], nomes[1]);
    inicializarQuadroCustomizar(quadroCustomizar, barra, deslizantes);
    inicializarBotoesCustomizar(quadro, botoes, botoesRet, botoesTexto);
    inicializarNomeCustomizar(quadroCustomizar, nomeCaixa, nomeRet);

    cores[0] = jogador1.cor;
    cores[1] = jogador2.cor;
    cores[2] = tabuleiro.corSuporte;
    sobreBotaoCor = {255, 246, 236, 255};

    carregarTexturaTabuleiro();
    carregarAudioCustomizar();
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
            if (escolha != 2) {
                tamNome = strlen(nomes[escolha]);
                nomePos = {nomeCaixa.retangulo.x + 10.0f, nomeCaixa.retangulo.y};
                inicializarTexto(nomeTexto, nomePos, nomes[escolha], 64.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold64());
            }
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
                        atualizarCorDeslizantes(deslizantes, cores[escolhido]);
                    }
                    break;
                }
            }
            if (escolhido != OPCAO_TRES && CheckCollisionPointRec((Vector2){mouse.x, mouse.y}, nomeCaixa.retangulo)) {
                mouse.tipoCursor = MOUSE_CURSOR_IBEAM;
                nomeCaixa.cor = sobreBotaoCor;
                nomeTexto.cor = sobreBotaoCor;

                int tecla = GetCharPressed();

                while (tecla > 0) {
                    if (tecla >= 32 && tecla <= 125 && tamNome < NOME_TAM) {
                        nomes[escolhido][tamNome] = tecla;
                        nomes[escolhido][tamNome+1] = '\0';
                        tamNome++;
                    }
                    tecla = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    tamNome--;
                    if (tamNome < 0)
                        tamNome = 0;
                    nomes[escolhido][tamNome] = '\0';
                }
                Vector2 temp = MeasureTextEx(obterOpenSansSemiBold16(), nomes[escolhido], 16.0f, 1.0f);
                textos[escolhido].posicao.x = quadro.x + (quadro.width - temp.x)/2;
            }
            else {
                nomeCaixa.cor = COR_FUNDO;
                nomeTexto.cor = COR_FUNDO;
            }
        }
        for (int i = 0; i < 2; i++) {
            if (mouseSobreCaixa(botoes[i], mouse)) {
                botoes[i].cor = sobreBotaoCor;
                botoesTexto[i].cor = sobreBotaoCor;
                if (!sobreBotao) {
                    tocarMouseSobre();
                    sobreBotao = true;
                    botaoSobre = i;
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mouse.click = true;
                    tocarBotaoClick();
                }
            } else {
                botoes[i].cor = COR_FUNDO;
                botoesTexto[i].cor = COR_FUNDO;
                if (botaoSobre == i) {
                    sobreBotao = false;
                }
            }
        }
        if (mouse.click) {
            if (botaoSobre == BOTAO_SAIR) {
                mouse.estadoEscolhido = -1;
                break;
            } else {
                falha = false;
                sucesso = false;
                int tamN1 = strlen(nomes[0]), tamN2 = strlen(nomes[1]);
                bool coresIguais = cores[0].r == cores[1].r &&
                                   cores[0].g == cores[1].g &&
                                   cores[0].b == cores[1].b;
                if (tamN1 == 0 || tamN2 == 0 || coresIguais) {
                    falha = true;
                    tocarSalvarFalha();
                } else if (salvarCustomizacao(cores, nomes)) {
                    sucesso = true;
                    atualizarNomeCor(jogador1, nomes[0], cores[0]);
                    atualizarNomeCor(jogador2, nomes[1], cores[1]);
                    tabuleiro.corSuporte = cores[2];
                    tocarSalvarSucesso();
                }
            }
        }

        manterMusicaTocando();
        BeginDrawing();
        ClearBackground(COR_FUNDO);
        SetMouseCursor(mouse.tipoCursor);
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
                desenharBotao(nomeCaixa, nomeTexto, 2.0f, 0.8f);
            }
        }
        if (falha) {
            DrawTextEx(obterOpenSansSemiBold32(), "FALHA: Nome vazio ou cores iguais", (Vector2){quadroCustomizar.x + 169.0f, 17.0f}, 32.0f, 1.0f, RED);
        }
        if (sucesso) {
            DrawTextEx(obterOpenSansSemiBold32(), "SUCESSO: Configuracoes salvas", (Vector2){quadroCustomizar.x + 191.0f, 17.0f}, 32.0f, 1.0f, GREEN);
        }
        desenharBotao(botoes[0], botoesTexto[0], 1.0f, 0.0f);
        desenharBotao(botoes[1], botoesTexto[1], 1.0f, 0.0f);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
    descarregarTexturaTabuleiro();
    descarregarAudioCustomizar();
}


void telaComoJogar(Mouse &mouse, bool &janelaAtiva) {
    Rectangle botaoRet;
    Caixa botao;
    Vector2 temp, pos;
    Texto botaoTexto;
    Color sobreBotaoCor = {255, 246, 236, 255};
    bool sobreBotao = false;

    botaoRet = {
        (64.0f + LARGURA)/2.0f - 64.0f, 48.0f + ALTURA - 96.0f - 75.0f,
        128.0f, 48.0f
    };
    inicializarCaixa(botao, botaoRet, 0.2f, 0, COR_FUNDO);
    temp = MeasureTextEx(obterOpenSansSemiBold32(), "Voltar", 32.0f, 1.0f);
    pos = {botaoRet.x + (botaoRet.width - temp.x)/2.0f, botaoRet.y + (botaoRet.height - temp.y)/2};
    inicializarTexto(botaoTexto, pos, "Voltar", 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());

    while (janelaAtiva) {
        lerMouse(mouse);

        if (CheckCollisionPointRec((Vector2){mouse.x, mouse.y}, botao.retangulo)) {
            botao.cor = sobreBotaoCor;
            botaoTexto.cor = sobreBotaoCor;
            if (!sobreBotao) {
                tocarMouseSobre();
                sobreBotao = true;
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                tocarBotaoClick();
                break;
            }
        } else {
            botao.cor = COR_FUNDO;
            botaoTexto.cor = COR_FUNDO;
            sobreBotao = false;
        }

        manterMusicaTocando();
        BeginDrawing();
        ClearBackground(COR_FUNDO);
        desenharComoJogar();
        desenharBotao(botao, botaoTexto, 1.0f, 0.0f);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
}
