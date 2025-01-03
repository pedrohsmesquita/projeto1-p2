/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com a lógica do funcionamento de menus (tela inicial, regras
 * customização).
 */
#ifndef MENU_H
#define MENU_H

#include "interface.h"
#include "jogador.h"
#include "mouse.h"
#include "audio.h"

void selecionarOpcaoCustomizar(Caixa caixas[], Mouse &mouse, bool opcaoSelecionada[], bool mouseSobre[], bool &selecionado);
void deslizantesAtualizarBarra(Rectangle deslizantes[], const Color &cor);
void atualizarCorDeslizantes(const Rectangle deslizantes[], Color &cor);
void inicializarOpcaoCustomizar(const Rectangle &quadro, Caixa caixas[], Rectangle textosRet[], Texto textos[], Jogador &jogador1, Jogador &jogador2);
void inicializarQuadroCustomizar(const Rectangle &quadroCustomizar, Rectangle barra[], Rectangle deslizantes[]);
void inicializarBotoesCustomizar(const Rectangle &quadro, Caixa caixas[], Rectangle ret[], Texto textos[]);
bool mouseSobreDeslizante(const Rectangle &deslizante, const Rectangle &deslizantes, const Mouse &mouse);

#endif // MENU_H

