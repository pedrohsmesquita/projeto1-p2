/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com a lógica e estados internos do jogo.
 */
#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "tabuleiro.h"
#include "mouse.h"
#include "interface.h"

void escolherColuna(const Tabuleiro &tabuleiro, Mouse &mouse);
void efetuarAcao(Jogador &jogador, Tabuleiro &tabuleiro, int linha, int coluna);
void consumarAcao(Celula &celula, const Jogador &jogador1, const Jogador &jogador2, float yf);
void atualizarPosicaoPeca(Celula &celula, float deltaT);
void calcularLinhaVitoria(Vector2 centros[], float &progresso);
void textoVitoria(char vitoria[], char nome[]);
void inicializarElementosVitEmp(Caixa &botaoVoltar, Caixa &botaoJogarNovamente, Color &corMouseSobre, Rectangle &jogarNovamenteRet, Rectangle &voltarRet, Texto &voltarText, Texto &jogarNovamenteText);
bool acaoValida(const Tabuleiro &tabuleiro, int coluna);
bool verificarVitoria(const Tabuleiro &tabuleiro, int linha, int coluna, Vector2 centrosPiPf[]);
bool empate(const Jogador &jogador1, const Jogador &jogador2);
void definirTurno(Jogador &jogador);
void trocarTurno(Jogador jogador[], int &jogadorTurno);
int obterVencedor(Celula &celula, Jogador &jogador1);

#endif // JOGO_H

