/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "jogador.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "jogador.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis pela l�gica e estado dos jogadores
 */
 #include "jogador.h"
 #include <cstring>

void jogadorEstadoInicial(Jogador& jogador, int id, Color cor, char nome[]) {
    jogador.id = id;
    jogador.pecas = 21;
    jogador.cor = cor;
    jogador.turno = false;
    jogador.vencedor = false;
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

void atualizarNomeCor(Jogador& jogador, const char nome[], Color cor) {
    jogador.cor = cor;
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

void resetarJogador(Jogador& jogador) {
    jogador.pecas = 21;
    jogador.vencedor = false;
}

void removerPeca(Jogador& jogador) {
    jogador.pecas--;
}
