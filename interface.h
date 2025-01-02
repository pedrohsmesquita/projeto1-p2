/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com elementos gerais da interface.
 *
 * Por enquanto, ainda não há nada para fazer aqui.
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "mouse.h"
#include "raylib.h"

#define COR_FUNDO CLITERAL(Color) {255, 251, 247, 255}
#define OPEN_SANS_LIGHT "assets/fonts/open-sans/OpenSans-Light.ttf"
#define OPEN_SANS_SEMIBOLD "assets/fonts/open-sans/OpenSans-Semibold.ttf"

struct Fontes {
    Font openSansLight;
    Font openSansSemibold16;
    Font openSansSemibold32;
};

struct Texto {
    Vector2 posicao;
    char *conteudo;
    float tamanho;
    float espacamento;
    Color cor;
    Font fonte;
};

struct Caixa {
    Rectangle retangulo;
    float redondeza;
    int segmentos;
    Color cor;
};

void inicializarCaixa(Caixa &caixa, Rectangle &retangulo, float redondeza, int segmentos, Color cor);
void inicializarTexto(Texto &texto, Vector2 &posicao, char *conteudo, float tam, float espac, Color cor, Font &fonte);
void carregarFonte();
bool mouseSobreCaixa(const Caixa &caixa, const Mouse &mouse);
Font& obterOpenSansLight();
Font& obterOpenSansSemiBold16();
Font& obterOpenSansSemiBold32();
void descarregarFonte();


#endif // INTERFACE_H
