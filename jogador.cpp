/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "jogador.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "jogador.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis pela l�gica e estado dos jogadores
 */
 #include "jogador.h"
 #include <cstring>

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, int cor, char *nome) {
    jogador.id = id;
    jogador.pecas = pecas;
    jogador.cor = cor;
    jogador.turno = false;
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

void removerPeca(Jogador &jogador) {
    jogador.pecas--;
}

void filaAcoesEstadoInicial(FilaAcoes &fila) {
    fila.fim = -1;
    fila.tam = 0;
}

void adicionarAcao(FilaAcoes &fila, Jogador *autor, int l, int c, float x, float y, float yf, float v, float a) {
    fila.fim = fila.fim + 1;
    fila.acao[fila.fim].autor = autor;
    fila.acao[fila.fim].linha = l;
    fila.acao[fila.fim].col = c;
    fila.acao[fila.fim].animacao.x = x;
    fila.acao[fila.fim].animacao.y = y;
    fila.acao[fila.fim].animacao.yf = yf;
    fila.acao[fila.fim].animacao.v = v;
    fila.acao[fila.fim].animacao.a = a;
    fila.acao[fila.fim].concluida = false;
    fila.tam++;
}
