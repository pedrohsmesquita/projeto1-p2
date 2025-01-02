/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "interface.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "interface.h". Todas as funções desse arquivo
 * deverão ser responsáveis pela lógica de elementos gerais da interface.
 */
#include "interface.h"

Fontes &obterFontes() {
    static Fontes fontes;

    return fontes;
}

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

void carregarFonte() {
    Fontes &fontes = obterFontes();
    int letrasNome[] = {'L', 'I', 'G'};
    int letra4[] = {'4'};

    //fontes.openSansLight = LoadFontEx(OPEN_SANS_LIGHT, 14.0f, nullptr, 0);
    fontes.openSansSemibold16 = LoadFontEx(OPEN_SANS_SEMIBOLD, 16.0f, nullptr, 0);
    fontes.openSansSemibold32 = LoadFontEx(OPEN_SANS_SEMIBOLD, 32.0f, nullptr, 0);
    fontes.boogaloo192 = LoadFontEx(BOOGALOO_FONT, 192.0f, letrasNome, 3);
    fontes.boogaloo256 = LoadFontEx(BOOGALOO_FONT, 256.0f, letra4, 1);
}

bool mouseSobreCaixa(const Caixa &caixa, const Mouse &mouse) {
    return mouse.x >= caixa.retangulo.x && mouse.x <= (caixa.retangulo.x + caixa.retangulo.width) &&
           mouse.y >= caixa.retangulo.y && mouse.y <= (caixa.retangulo.y + caixa.retangulo.height);
}

Font& obterOpenSansLight() {
    Fontes &fontes = obterFontes();

    return fontes.openSansLight;
}

Font& obterOpenSansSemiBold16() {
    Fontes &fontes = obterFontes();

    return fontes.openSansSemibold16;
}

Font& obterOpenSansSemiBold32() {
    Fontes &fontes = obterFontes();

    return fontes.openSansSemibold32;
}

Font& obterBoogaloo192() {
    Fontes &fontes = obterFontes();

    return fontes.boogaloo192;
}

Font& obterBoogaloo256() {
    Fontes &fontes = obterFontes();

    return fontes.boogaloo256;
}

void descarregarFonte() {
    Fontes &fontes = obterFontes();

    //UnloadFont(fontes.openSansLight);
    UnloadFont(fontes.openSansSemibold16);
    UnloadFont(fontes.openSansSemibold32);
    UnloadFont(fontes.boogaloo192);
    UnloadFont(fontes.boogaloo256);
}
