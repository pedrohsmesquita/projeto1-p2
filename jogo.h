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
void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int linha, int coluna);
void consumarAcao(Celula &celula, const Jogador &jogador1, const Jogador &jogador2, float yf);
void atualizarPosicaoPeca(Celula &celula, float deltaT);
bool acaoValida(const Tabuleiro &tabuleiro, int coluna);
bool verificarVitoria(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
bool empate(const Jogador &jogador1, const Jogador &jogador2);
Jogador *definirTurno(Jogador &jogador);
Jogador *trocarTurno(Jogador &jogador1, Jogador &jogador2);

#endif // JOGO_H

