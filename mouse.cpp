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
    mouse.click = false;
 }
