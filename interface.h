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
#include "audio.h"
#include "raylib.h"

#define BOTAO_SAIR_VOLTAR 0
#define BOTAO_PROSSEGUIR_OK 1
#define OPCOES_COR CLITERAL(Color) {169, 169, 169, 255}
#define OPCOES_COR_MOUSE CLITERAL(Color) {80, 76, 76, 255}
#define COR_FUNDO CLITERAL(Color) {255, 251, 247, 255}
#define OPEN_SANS_LIGHT "assets/fonts/open-sans/OpenSans-Light.ttf"
#define OPEN_SANS_SEMIBOLD "assets/fonts/open-sans/OpenSans-Semibold.ttf"
#define BOOGALOO_FONT "assets/fonts/boogaloo/Boogaloo-Regular.ttf"
#define LARGURA 1024
#define ALTURA 768

struct Fontes {
    Font openSansSemibold16;
    Font openSansSemibold32;
    Font openSansSemibold64;
    Font boogaloo192;
    Font boogaloo256;
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
void interacaoBotao(Caixa &botao, Texto &texto, Mouse &mouse, Color &corInteracao, bool &mouseSobreBotao, int estadoEscolhido);
Font& obterOpenSansSemiBold16();
Font& obterOpenSansSemiBold32();
Font& obterOpenSansSemiBold64();
Font& obterBoogaloo192();
Font& obterBoogaloo256();
void descarregarFonte();


#endif // INTERFACE_H
