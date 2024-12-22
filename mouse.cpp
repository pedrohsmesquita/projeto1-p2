/**
 * Este arquivo deve ser utilizado para definir as fun��es declaradas no
 * arquivo "mouse.h". Qualquer fun��o feita aqui deve seguir o seu prot�tipo
 * como exatamente foi declarado em "mouse.h". Todas as fun��es desse arquivo
 * dever�o ser respons�veis por lidar com a leitura e manipula��o do estado
 * da estrutura Mouse.
 */
 #include "mouse.h"

 void lerMouse(Mouse &mouse) {
    mouse.x = GetMouseX();
    mouse.y = GetMouseY();
    mouse.estadoEscolhido = -1;
    mouse.tipoCursor = MOUSE_CURSOR_DEFAULT;
    mouse.click = false;
 }
