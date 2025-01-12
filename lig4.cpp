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

void processarAcaoJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Mouse &mouse);
void atualizarJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Vector2 centrosVPiPf[], Mouse &mouse);
bool atualizarPosJogo(const Mouse &mouse);
bool loopJogoAtivo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Vector2 centrosVPiPf[], Mouse &mouse, bool &janelaAtiva);
bool loopPosJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Vector2 centrosVPiPf[], Mouse &mouse, bool &janelaAtiva);

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
        if (!loopJogoAtivo(tabuleiro, jogador1, jogador2, jogadorPtr, centrosVPiPf, mouse, janelaAtiva)) {
            break;
        }
        if (tabuleiro.estado.vitoria || tabuleiro.estado.empate) {
            if (!loopPosJogo(tabuleiro, jogador1, jogador2, centrosVPiPf, mouse, janelaAtiva))
                break;
        }
        if (jogador1.turno) {
            jogadorPtr = &jogador1;
        } else {
            jogadorPtr = &jogador2;
        }
    }
    jogador1.turno = false;
    jogador2.turno = false;
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
    bool mouseSobre[3] = {false, false, false}, falha = false;
    bool opcaoSelecionada[3] = {false, false, false}, selecionado = false, sucesso = false;
    bool sobreSalvar = false, sobreSair = false;
    int escolha, escolhido = -1, botaoSobre = -1, tamNome;

    inicializarElementosCustomizar(tabuleiro, jogador1, jogador2, quadro, quadroCustomizar, nomes, cores, sobreBotaoCor);
    inicializarOpcaoCustomizar(quadro, caixas, textosRet, textos, nomes[0], nomes[1]);
    inicializarQuadroCustomizar(quadroCustomizar, barra, deslizantes);
    inicializarBotoesCustomizar(quadro, botoes, botoesRet, botoesTexto);
    inicializarNomeCustomizar(quadroCustomizar, nomeCaixa, nomeRet);
    carregarTexturaTabuleiro();
    carregarAudioCustomizar();

    while (janelaAtiva) {
        lerMouse(mouse);
        selecionarOpcaoCustomizar(caixas, mouse, opcaoSelecionada, mouseSobre, selecionado);
        escolha = mouse.estadoEscolhido;
        // Remover seleção caso ESC seja pressionado
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
        interacaoBotao(botoes[0], botoesTexto[0], mouse, sobreBotaoCor, sobreSalvar, BOTAO_PROSSEGUIR_OK);
        interacaoBotao(botoes[1], botoesTexto[1], mouse, sobreBotaoCor, sobreSair, BOTAO_SAIR_VOLTAR);
        if (mouse.click) {
            tocarBotaoClick();
            if (!botaoCustomizarAcao(tabuleiro, jogador1, jogador2, mouse, cores, nomes, falha, sucesso))
                break;
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
            DrawTextEx(obterOpenSansSemiBold32(), "SUCESSO: Customizacoes salvas", (Vector2){quadroCustomizar.x + 191.0f, 17.0f}, 32.0f, 1.0f, GREEN);
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
        interacaoBotao(botao, botaoTexto, mouse, sobreBotaoCor, sobreBotao, BOTAO_SAIR_VOLTAR);
        if (mouse.click) {
            tocarBotaoClick();
            break;
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

void processarAcaoJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Mouse &mouse) {
    lerMouse(mouse);
    escolherColuna(tabuleiro, mouse);
    int coluna = mouse.estadoEscolhido;
    if (mouse.click && acaoValida(tabuleiro, coluna)) {
        int linha = tabuleiro.linhasLivres[coluna];
        efetuarAcao(*jogadorPtr, tabuleiro, linha, coluna);
        jogadorPtr = trocarTurno(jogador1, jogador2);
    }
}

void atualizarJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Vector2 centrosVPiPf[], Mouse &mouse) {
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
                } else if (empate(jogador1, jogador2)) {
                    tabuleiro.estado.empate = true;
                }
                tocarPecaClick();
            }
        }
    }
}

bool loopJogoAtivo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Jogador *&jogadorPtr, Vector2 centrosVPiPf[], Mouse &mouse, bool &janelaAtiva) {
    while (janelaAtiva) {
        processarAcaoJogo(tabuleiro, jogador1, jogador2, jogadorPtr, mouse);
        atualizarJogo(tabuleiro, jogador1, jogador2, jogadorPtr, centrosVPiPf, mouse);
        if (tabuleiro.estado.vitoria) {
            tocarVitoria();
            return tabuleiro.estado.vitoria;
        }
        if (tabuleiro.estado.empate) {
            return tabuleiro.estado.empate;
        }

        manterMusicaTocando();
        BeginDrawing();
        desenharTabuleiro(tabuleiro, mouse);
        desenharPerfil(jogador1, 150);
        desenharPerfil(jogador2, 468);
        EndDrawing();
        janelaAtiva = !WindowShouldClose();
    }
    return janelaAtiva;
}

bool loopPosJogo(Tabuleiro &tabuleiro, Jogador &jogador1, Jogador &jogador2, Vector2 centrosVPiPf[], Mouse &mouse, bool &janelaAtiva) {
    Caixa botaoVoltar, botaoJogarNovamente;
    Color corMouseSobre;
    Rectangle jogarNovamenteRet, voltarRet;
    Texto voltarText, jogarNovamenteText;
    float linhaProgresso = 0.0f;
    bool mouseSobreJogar = false, mouseSobreVoltar = false;

    inicializarElementosVitEmp(botaoVoltar, botaoJogarNovamente, corMouseSobre, jogarNovamenteRet, voltarRet, voltarText, jogarNovamenteText);

    while (janelaAtiva) {
        lerMouse(mouse);
        if (tabuleiro.estado.vitoria && linhaProgresso < 1.0f) {
            calcularLinhaVitoria(centrosVPiPf, linhaProgresso);
        }
        interacaoBotao(botaoJogarNovamente, jogarNovamenteText, mouse, corMouseSobre, mouseSobreJogar, BOTAO_PROSSEGUIR_OK);
        interacaoBotao(botaoVoltar, voltarText, mouse, corMouseSobre, mouseSobreVoltar, BOTAO_SAIR_VOLTAR);
        if (mouse.click) {
            tocarBotaoClick();
            return atualizarPosJogo(mouse);
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
    return janelaAtiva;
}

bool atualizarPosJogo(const Mouse &mouse) {
    switch (mouse.estadoEscolhido) {
    case BOTAO_SAIR_VOLTAR:
        return false;
    case BOTAO_PROSSEGUIR_OK:
        return true;
    }
}
