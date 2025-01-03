#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <iostream>
#include <fstream>
#include "raylib.h"

#define ARQUIVO_PATH "customizacao.bin"

bool salvarCustomizacao(Color cor[], char nomes[2][13]);
bool carregarCustomizacao(Color cor[], char nomes[2][13]);


#endif // ARQUIVO_H
