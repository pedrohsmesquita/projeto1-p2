#include "audio.h"

Audio& obterAudio();

Audio& obterAudio() {
    static Audio audio;

    return audio;
}

void carregaAudio() {
    Audio& audio = obterAudio();

    audio.musica = LoadMusicStream(MUSICA_FUNDO);
}

void descarregarAudio() {
    Audio& audio = obterAudio();

    UnloadMusicStream(audio.musica);
}

void tocarMusicaFundo() {
    Audio& audio = obterAudio();

    PlayMusicStream(audio.musica);
}

void manterMusicaTocando() {
    static const Audio& audio = obterAudio();

    UpdateMusicStream(audio.musica);
}

void carregarPecasAudio() {
    Audio& audio = obterAudio();

    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        audio.pecaClick[i] = LoadSound(PECAS_CLICK_SOM);
    }
}

void descarregarPecasAudio() {
    Audio& audio = obterAudio();

    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        UnloadSound(audio.pecaClick[i]);
    }
}

void tocarPecaClick() {
    static const Audio& audio = obterAudio();
    static int i = 0;

    PlaySound(audio.pecaClick[i++]);
    if (i >= TAM_PECAS_CLICK_ARR) {
        i = 0;
    }
}
