#include "audio.h"

Audio audio;

void carregarAudio() {
    audio.musica = LoadMusicStream(MUSICA_FUNDO);
    audio.botaoClick = LoadSound(BOTAO_CLICK);
    for (int i = 0; i < 2; i++) {
        audio.mouseSobre[i] = LoadSound(MOUSE_SOBRE);
    }
}

void descarregarAudio() {
    UnloadMusicStream(audio.musica);
    UnloadSound(audio.botaoClick);
    for (int i = 0; i < 2; i++) {
        UnloadSound(audio.mouseSobre[i]);
    }
}

void tocarMusicaFundo() {
    PlayMusicStream(audio.musica);
}

void manterMusicaTocando() {
    UpdateMusicStream(audio.musica);
}

void carregarAudioJogo() {
    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        audio.pecaClick[i] = LoadSound(PECAS_CLICK_SOM);
    }
    audio.vitoria = LoadSound(VITORIA_SOM);
}

void descarregarAudioJogo() {
    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        UnloadSound(audio.pecaClick[i]);
    }
    UnloadSound(audio.vitoria);
}

void carregarAudioCustomizar() {
    audio.salvarSucesso = LoadSound(SALVAR_SUCESSO);
    audio.salvarFalha = LoadSound(SALVAR_FALHA);
}

void descarregarAudioCustomizar() {
    UnloadSound(audio.salvarSucesso);
    UnloadSound(audio.salvarFalha);
}

void tocarPecaClick() {
    static int i = 0;

    PlaySound(audio.pecaClick[i++]);
    if (i >= TAM_PECAS_CLICK_ARR) {
        i = 0;
    }
}

void tocarMouseSobre() {
    static int i = 0;

    PlaySound(audio.mouseSobre[i++]);
    if (i >= 2) {
        i = 0;
    }
}

void tocarBotaoClick() {
    PlaySound(audio.botaoClick);
}

void tocarVitoria() {
    PlaySound(audio.vitoria);
}

void tocarSalvarSucesso() {
    PlaySound(audio.salvarSucesso);
}

void tocarSalvarFalha() {
    PlaySound(audio.salvarFalha);
}
