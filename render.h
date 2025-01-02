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
#include "interface.h"

struct Texturas {
    Texture2D tabuleiro;
};

void desenharTabuleiro(const Tabuleiro &tabuleiro, const Mouse &mouse);
void linhaVitoria(const Vector2 centro[]);
void desenharPerfil(const Jogador &jogador, float y);
void desenharBotao(const Caixa &caixa, const Texto &texto);
void carregarTexturaTabuleiro();
void descarregarTexturaTabuleiro();

#endif // RENDER_H
