/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "interface.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "interface.h". Todas as funções desse arquivo
 * deverão ser responsáveis pela lógica de elementos gerais da interface.
 */
#include "interface.h"

Fontes fontes;

void inicializarCaixa(Caixa &caixa, Rectangle &retangulo, float redondeza, int segmentos, Color cor) {
    caixa.retangulo = retangulo;
    caixa.redondeza = redondeza;
    caixa.segmentos = segmentos;
    caixa.cor = cor;
}

void inicializarTexto(Texto &texto, Vector2 &posicao, char *conteudo, float tam, float espac, Color cor, Font &fonte) {
    texto.posicao = posicao;
    texto.conteudo = conteudo;
    texto.tamanho = tam;
    texto.espacamento = espac;
    texto.cor = cor;
    texto.fonte = fonte;
}

void interacaoBotao(Caixa &botao, Texto &texto, Mouse &mouse, Color &corInteracao, bool &mouseSobreBotao, int estadoEscolhido) {
    if (mouseSobreCaixa(botao, mouse)) {
        botao.cor = corInteracao;
        texto.cor = corInteracao;
        if (!mouseSobreBotao) {
            tocarMouseSobre();
            mouseSobreBotao = true;
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse.estadoEscolhido = estadoEscolhido;
            mouse.click = true;
        }
    } else {
        botao.cor = COR_FUNDO;
        texto.cor = COR_FUNDO;
        mouseSobreBotao = false;
    }
}

void carregarFonte() {
    int letrasNome[] = {'L', 'I', 'G'};
    int letra4[] = {'4'};

    fontes.openSansSemibold16 = LoadFontEx(OPEN_SANS_SEMIBOLD, 16.0f, nullptr, 0);
    fontes.openSansSemibold32 = LoadFontEx(OPEN_SANS_SEMIBOLD, 32.0f, nullptr, 0);
    fontes.openSansSemibold64 = LoadFontEx(OPEN_SANS_SEMIBOLD, 64.0f, nullptr, 0);
    fontes.boogaloo192 = LoadFontEx(BOOGALOO_FONT, 192.0f, letrasNome, 3);
    fontes.boogaloo256 = LoadFontEx(BOOGALOO_FONT, 256.0f, letra4, 1);
}

void descarregarFonte() {
    UnloadFont(fontes.openSansSemibold16);
    UnloadFont(fontes.openSansSemibold32);
    UnloadFont(fontes.openSansSemibold64);
    UnloadFont(fontes.boogaloo192);
    UnloadFont(fontes.boogaloo256);
}

bool igualdadeCor(const Color &cor1, const Color &cor2) {
    return cor1.r == cor2.r && cor1.g == cor2.g & cor1.b == cor2.b;
}

bool mouseSobreCaixa(const Caixa &caixa, const Mouse &mouse) {
    return mouse.x >= caixa.retangulo.x && mouse.x <= (caixa.retangulo.x + caixa.retangulo.width) &&
           mouse.y >= caixa.retangulo.y && mouse.y <= (caixa.retangulo.y + caixa.retangulo.height);
}

Font& obterOpenSansSemiBold16() {
    return fontes.openSansSemibold16;
}

Font& obterOpenSansSemiBold32() {
    return fontes.openSansSemibold32;
}

Font& obterOpenSansSemiBold64() {
    return fontes.openSansSemibold64;
}

Font& obterBoogaloo192() {
    return fontes.boogaloo192;
}

Font& obterBoogaloo256() {
    return fontes.boogaloo256;
}

