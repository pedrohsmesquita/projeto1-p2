#include "arquivo.h"

bool salvarCustomizacao(Color cor[], const char nomes[2][13]) {
    std::ofstream arquivo(ARQUIVO_PATH, std::ios::binary);

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo.write((const char *)(cor), 3 * sizeof(Color));
    arquivo.write(nomes[0], 13);
    arquivo.write(nomes[1], 13);
    arquivo.close();
    return true;
}

bool carregarCustomizacao(Color cor[], char nomes[2][13]) {
    std::ifstream arquivo(ARQUIVO_PATH, std::ios::binary);

    if (!arquivo.is_open()) {
        return false;
    }

    arquivo.read((char *)(cor), 3 * sizeof(Color));
    arquivo.read(nomes[0], 13);
    arquivo.read(nomes[1], 13);
    arquivo.close();
    return true;
}
