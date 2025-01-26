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
#include "tabuleiro.h"
#include "mouse.h"
#include "audio.h"
#include "arquivo.h"
#include <cstring>

#define OPCAO_UM 0
#define OPCAO_DOIS 1
#define OPCAO_TRES 2
#define BOTAO_SALVAR 0
#define BOTAO_SAIR 1

void selecionarOpcaoCustomizar(Caixa caixas[], Mouse& mouse, bool opcaoSelecionada[], bool mouseSobre[], bool& selecionado);
void alterarNome(Texto textos[], const Rectangle& quadro, char nomes[2][NOME_TAM+1], int& tamNome, int escolhido);
void deslizantesAtualizarBarra(Rectangle deslizantes[], const Color& cor);
void atualizarCorDeslizantes(const Rectangle deslizantes[], Color& cor);
void inicializarElementosCustomizar(const Tabuleiro& tabuleiro, const Jogador& jogador1, const Jogador& jogador2, Rectangle& quadro, Rectangle& quadroCustomizar, char nomes[2][NOME_TAM+1], Color cores[], Color& sobreBotaoCor);
void inicializarOpcaoCustomizar(const Rectangle& quadro, Caixa caixas[], Rectangle textosRet[], Texto textos[], char nome1[], char nome2[]);
void inicializarQuadroCustomizar(const Rectangle& quadroCustomizar, Rectangle barra[], Rectangle deslizantes[]);
void inicializarBotoesCustomizar(const Rectangle& quadro, Caixa caixas[], Rectangle ret[], Texto textos[]);
void inicializarNomeCustomizar(const Rectangle& quadroCustomizar, Caixa& caixa, Rectangle& ret, Vector2& nomePos);
bool mouseSobreDeslizante(const Rectangle& barra, const Rectangle& deslizantes, const Mouse& mouse);
bool botaoCustomizarAcao(Tabuleiro& tabuleiro, Jogador& jogador1, Jogador& jogador2, Mouse& mouse, Color cores[], char nomes[2][NOME_TAM+1], bool& falha, bool& sucesso);

#endif // MENU_H

