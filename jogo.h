/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com a lógica e estados internos do jogo.
 */
#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "tabuleiro.h"

int escolherColuna(const Tabuleiro &tabuleiro);
void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int coluna);
bool verificarVitoria(const Jogador &jogador, const Tabuleiro &tabuleiro, int l, int c);

#endif // JOGO_H

