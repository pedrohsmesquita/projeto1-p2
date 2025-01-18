/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados ao fluxo do jogo.
 */
#ifndef LIG4_H
#define LIG4_H

#include "interface.h"
#include "mouse.h"
#include "jogador.h"
#include "tabuleiro.h"

void telaJogo(Jogador jogador[], Tabuleiro& tabuleiro, Mouse& mouse, bool& janelaAtiva);
void telaCustomizar(Jogador& jogador1, Jogador& jogador2, Tabuleiro& tabuleiro, Mouse& mouse, bool& janelaAtiva);
void telaComoJogar(Mouse& mouse, bool& janelaAtiva);

#endif // LIG4_H
