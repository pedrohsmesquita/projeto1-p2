/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "menu.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "menu.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis por permitir que o usu�rio interaja com elementos
 * dos menus.
 */
#include "menu.h"

void selecionarOpcaoCustomizar(Caixa caixas[], Mouse& mouse, bool opcaoSelecionada[], bool mouseSobre[], bool& selecionado) {
    for (int i = 0; i < 3; i++) {
        if (mouseSobreCaixa(caixas[i], mouse)) {
            if (!mouseSobre[i]) {
                caixas[i].cor = (Color) {255, 239, 221, 156};
                mouseSobre[i] = true;
                tocarMouseSobre();
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int j;
                for (j = 0; j < 3; j++) {
                    if (opcaoSelecionada[j])
                        break;
                }
                if (j < 3 && j != i) {
                    opcaoSelecionada[j] = false;
                    caixas[j].cor = COR_FUNDO;
                    opcaoSelecionada[i] = true;
                    tocarBotaoClick();
                } else if (j == 3) {
                    opcaoSelecionada[i] = true;
                    tocarBotaoClick();
                }
                mouse.estadoEscolhido = i;
                selecionado = true;
            }
        } else {
            if (!opcaoSelecionada[i]) {
                caixas[i].cor = COR_FUNDO;
            }
            mouseSobre[i] = false;
        }
    }
}

void alterarNome(Texto textos[], const Rectangle& quadro, char nomes[2][NOME_TAM+1], int& tamNome, int escolhido) {
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

void deslizantesAtualizarBarra(Rectangle deslizantes[], const Color& cor) {
    const float partesBarra = 2.499f;

    deslizantes[0].x = 306.0f + cor.r * partesBarra;
    deslizantes[1].x = 306.0f + cor.g * partesBarra;
    deslizantes[2].x = 306.0f + cor.b * partesBarra;
    if (deslizantes[0].x > 943) {
        deslizantes[0].x = 943;
    }
    if (deslizantes[1].x > 943) {
        deslizantes[1].x = 943;
    }
    if (deslizantes[2].x > 943) {
        deslizantes[2].x = 943;
    }
}

void atualizarCorDeslizantes(const Rectangle deslizantes[], Color& cor) {
    const float partesCor = 0.4005;
    float r, g, b;

    r = (deslizantes[0].x - 306.0f) * partesCor;
    g = (deslizantes[1].x - 306.0f) * partesCor;
    b = (deslizantes[2].x - 306.0f) * partesCor;

    if (r > 255.0f) {
        r = 255.0f;
    }
    if (g > 255.0f) {
        g = 255.0f;
    }
    if (b > 255.0f) {
        b = 255.0f;
    }

    cor.r = r;
    cor.g = g;
    cor.b = b;
}

void inicializarElementosCustomizar(const Tabuleiro& tabuleiro, const Jogador& jogador1, const Jogador& jogador2, Rectangle& quadro, Rectangle& quadroCustomizar, char nomes[2][NOME_TAM+1], Color cores[], Color& sobreBotaoCor) {
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

    cores[0] = jogador1.cor;
    cores[1] = jogador2.cor;
    cores[2] = tabuleiro.corSuporte;
    sobreBotaoCor = {255, 246, 236, 255};
}

void inicializarOpcaoCustomizar(const Rectangle& quadro, Caixa caixas[], Rectangle textosRet[], Texto textos[], char nome1[], char nome2[]) {
    Vector2 temp, textoPos;

    temp = MeasureTextEx(obterOpenSansSemiBold16(), nome1, 16.0f, 1.0f);
    textoPos = {
        quadro.x + (quadro.width - temp.x)/2, quadro.y + (50 - temp.y)/2
    };
    textosRet[0] = {
        quadro.x + 3.0f, quadro.y + 3.0f,
        quadro.width - 6.0f, 50.0f - 6.0f
    };
    inicializarCaixa(caixas[0], textosRet[0], 0.3f, 0, COR_FUNDO);
    inicializarTexto(textos[0], textoPos, nome1, 16.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold16());

    temp = MeasureTextEx(obterOpenSansSemiBold16(), nome2, 16.0f, 1.0f);
    textoPos = {
        quadro.x + (quadro.width - temp.x)/2, textosRet[0].y + textosRet[0].height + (50 - temp.y)/2
    };
    textosRet[1] = {
        textosRet[0].x, textosRet[0].y + textosRet[0].height + 5.0f,
        textosRet[0].width, textosRet[0].height
    };
    inicializarCaixa(caixas[1], textosRet[1], 0.3f, 0, COR_FUNDO);
    inicializarTexto(textos[1], textoPos, nome2, 16.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold16());

    temp = MeasureTextEx(obterOpenSansSemiBold16(), "Tabuleiro", 16.0f, 1.0f);
    textoPos = {
        quadro.x + (quadro.width - temp.x)/2, textosRet[1].y + textosRet[1].height + (50 - temp.y)/2
    };
    textosRet[2] = {
        textosRet[1].x, textosRet[1].y + textosRet[1].height + 5.0f,
        textosRet[1].width, textosRet[1].height
    };
    inicializarCaixa(caixas[2], textosRet[2], 0.3f, 0, COR_FUNDO);
    inicializarTexto(textos[2], textoPos, "Tabuleiro", 16.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold16());
}

void inicializarQuadroCustomizar(const Rectangle& quadroCustomizar, Rectangle barra[], Rectangle deslizantes[]) {
    barra[0] = {
        quadroCustomizar.x + 50.f, quadroCustomizar.y + quadroCustomizar.height - 250.0f,
        quadroCustomizar.width - 100.0f, 8.0f
    };
    barra[1] = {
        barra[0].x, barra[0].y + 50.0f,
        barra[0].width, barra[0].height
    };
    barra[2] = {
        barra[1].x, barra[1].y + 50.f,
        barra[1].width, barra[0].height
    };

    deslizantes[0] = {
        quadroCustomizar.x + 50.0f - 3, quadroCustomizar.y + quadroCustomizar.height - 250.0f - 14.0f,
        6.0f, 35.0f
    };
    deslizantes[1] = {
        deslizantes[0].x, deslizantes[0].y + 50.0f,
        6.0f, 35.0f
    };
    deslizantes[2] = {
        deslizantes[0].x, deslizantes[1].y + 50.0f,
        6.0f, 35.0f
    };
}

void inicializarBotoesCustomizar(const Rectangle& quadro, Caixa caixas[], Rectangle ret[], Texto textos[]) {
    Vector2 temp, textoPos;

    ret[0] = {
        quadro.x, quadro.y + quadro.height + 60.0f,
        quadro.width, 48.0f
    };
    temp = MeasureTextEx(obterOpenSansSemiBold32(), "Salvar", 32.0f, 1.0f);
    textoPos = {
        ret[0].x + (ret[0].width - temp.x)/2,
        ret[0].y + (ret[0].height - temp.y)/2
    };
    inicializarCaixa(caixas[0], ret[0], 0.2f, 0, COR_FUNDO);
    inicializarTexto(textos[0], textoPos, "Salvar", 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());

    ret[1] = {
        ret[0].x, ret[0].y + ret[0].height + 20.f,
        ret[0].width, ret[0].height
    };
    temp = MeasureTextEx(obterOpenSansSemiBold32(), "Voltar", 32.0f, 1.0f);
    textoPos = {
        ret[1].x + (ret[1].width - temp.x)/2,
        ret[1].y + (ret[1].height - temp.y)/2
    };
    inicializarCaixa(caixas[1], ret[1], 0.2f, 0, COR_FUNDO);
    inicializarTexto(textos[1], textoPos, "Voltar", 32.0f, 1.0f, COR_FUNDO, obterOpenSansSemiBold32());
}

void inicializarNomeCustomizar(const Rectangle& quadroCustomizar, Caixa& caixa, Rectangle& ret, Vector2& nomePos) {
    ret = {
        quadroCustomizar.x + 50.0f, quadroCustomizar.y + quadroCustomizar.height - 100.0f,
        quadroCustomizar.width - 100.f, 75.0f
    };
    inicializarCaixa(caixa, ret, 0.2f, 0, COR_FUNDO);
    nomePos = {caixa.retangulo.x + 10.0f, caixa.retangulo.y};
}

bool mouseSobreDeslizante(const Rectangle& barra, const Rectangle& deslizantes, const Mouse& mouse) {
    return mouse.x >= barra.x && mouse.x <= barra.x + barra.width - 6    &&
           ((mouse.y >= barra.y && mouse.y <= barra.y + barra.height) ||
            (mouse.y >= deslizantes.y && mouse.y <= deslizantes.y + deslizantes.width));
}

bool botaoCustomizarAcao(Tabuleiro& tabuleiro, Jogador& jogador1, Jogador& jogador2, Mouse& mouse, Color cores[], char nomes[2][NOME_TAM+1], bool& falha, bool& sucesso) {
    if (mouse.estadoEscolhido == BOTAO_SAIR_VOLTAR) {
        mouse.estadoEscolhido = -1;
        return false;
    }

    falha = false;
    sucesso = false;
    int tamN1 = strlen(nomes[0]), tamN2 = strlen(nomes[1]);
    bool coresIguais = igualdadeCor(cores[0], cores[1]);
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

    return true;
}
