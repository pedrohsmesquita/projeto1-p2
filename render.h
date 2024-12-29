/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com a interface gráfica do programa.
 */
#ifndef RENDER_H
#define RENDER_H

#include "tabuleiro.h"
#include "jogador.h"
#include "mouse.h"

void desenharTabuleiro(const Tabuleiro &tabuleiro, Mouse &mouse, const Vector2 centro[]);
void descarregarTexturaTabuleiro();

#endif // RENDER_H
