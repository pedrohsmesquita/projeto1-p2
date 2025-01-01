/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os prot�tipos das fun��es, ambos diretamente
 * relacionados com a interface gr�fica do programa.
 */
#ifndef RENDER_H
#define RENDER_H

#include "tabuleiro.h"
#include "jogador.h"
#include "mouse.h"
#include "interface.h"

void desenharTabuleiro(const Tabuleiro &tabuleiro, const Mouse &mouse);
void linhaVitoria(const Vector2 centro[]);
void desenharPerfil(const Jogador &jogador, float y);
void descarregarTexturaTabuleiro();

#endif // RENDER_H
