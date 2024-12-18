/**
 * Este arquivo deve ser utilizado para definir as funções declaradas no
 * arquivo "mouse.h". Qualquer função feita aqui deve seguir o seu protótipo
 * como exatamente foi declarado em "mouse.h". Todas as funções desse arquivo
 * deverão ser responsáveis por lidar com a leitura e manipulação do estado
 * da estrutura Mouse.
 */
 #include "mouse.h"

 void lerMouse(Mouse &mouse) {
    mouse.x = GetMouseX();
    mouse.y = GetMouseY();
    mouse.estadoEscolhido = -1;
    mouse.tipoCursor = MOUSE_CURSOR_DEFAULT;
 }

int obterMouseX(const Mouse &mouse) {
    return mouse.x;
}

int obterMouseY(const Mouse &mouse) {
    return mouse.y;
}

void definirMouseEstado(Mouse &mouse, int estado) {
    mouse.estadoEscolhido = estado;
}

int obterMouseEstado(const Mouse &mouse) {
    return mouse.estadoEscolhido;
}

void definirTipoCursor(Mouse &mouse, MouseCursor tipo) {
    mouse.tipoCursor = tipo;
}

MouseCursor obterTipoCursor(const Mouse &mouse) {
    return mouse.tipoCursor;
}
