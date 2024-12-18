/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os prot�tipos das fun��es, ambos diretamente
 * relacionados com a l�gica e estados internos do jogo.
 */
#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "tabuleiro.h"
#include "mouse.h"

void escolherColuna(const Tabuleiro &tabuleiro, Mouse &mouse);
void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int coluna);
bool acaoValida(const Tabuleiro &tabuleiro, int coluna);
bool verificarVitoria(const Jogador &jogador, const Tabuleiro &tabuleiro, int l, int c);

#endif // JOGO_H

