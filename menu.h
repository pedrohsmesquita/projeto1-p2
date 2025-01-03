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

#define OPCAO_UM 0
#define OPCAO_DOIS 1
#define OPCAO_TRES 2
#define BOTAO_SALVAR 0
#define BOTAO_SAIR 1

void selecionarOpcaoCustomizar(Caixa caixas[], Mouse &mouse, bool opcaoSelecionada[], bool mouseSobre[], bool &selecionado);
void deslizantesAtualizarBarra(Rectangle deslizantes[], const Color &cor);
void atualizarCorDeslizantes(const Rectangle deslizantes[], Color &cor);
void inicializarOpcaoCustomizar(const Rectangle &quadro, Caixa caixas[], Rectangle textosRet[], Texto textos[], char nome1[], char nome2[]);
void inicializarQuadroCustomizar(const Rectangle &quadroCustomizar, Rectangle barra[], Rectangle deslizantes[]);
void inicializarBotoesCustomizar(const Rectangle &quadro, Caixa caixas[], Rectangle ret[], Texto textos[]);
void inicializarNomeCustomizar(const Rectangle &quadroCustomizar, Caixa &caixa, Rectangle &ret);
bool mouseSobreDeslizante(const Rectangle &deslizante, const Rectangle &deslizantes, const Mouse &mouse);

#endif // MENU_H

