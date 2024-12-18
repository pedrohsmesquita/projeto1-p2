/**
 * Este arquivo deve ser utilizado apenas para declarar tipos de dados como
 * structs, unions e enums ou para os protótipos das funções, ambos diretamente
 * relacionados com a entrada de dados pelo mouse.
 */
#ifndef MOUSE_H
#define MOUSE_H

#include <raylib.h>

struct Mouse {
    int x;
    int y;
    int estadoEscolhido;
    MouseCursor tipoCursor;
};

void lerMouse(Mouse &mouse);
int obterMouseX(const Mouse &mouse);
int obterMouseY(const Mouse &mouse);
void definirMouseEstado(Mouse &mouse, int estado);
int obterMouseEstado(const Mouse &mouse);
void definirTipoCursor(Mouse &mouse, MouseCursor tipo);
MouseCursor obterTipoCursor(const Mouse &mouse);


#endif // MOUSE_H
