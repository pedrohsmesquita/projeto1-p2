/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "jogador.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "jogador.h". Todas as funções desse arquivo
 * deverão ser responsáveis pela lógica e estado dos jogadores
 */
 #include "jogador.h"
 #include <cstring>

void jogadorEstadoInicial(Jogador &jogador, int id, int pecas, Color cor, char *nome) {
    jogador.id = id;
    jogador.pecas = pecas;
    jogador.cor = cor;
    jogador.turno = false;
    jogador.vencedor = false;
    strncpy(jogador.nome, nome, NOME_TAM+1);
}

void removerPeca(Jogador &jogador) {
    jogador.pecas--;
}
