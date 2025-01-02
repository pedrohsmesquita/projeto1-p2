#include "audio.h"

Audio& obterAudio();

Audio& obterAudio() {
    static Audio audio;

    return audio;
}

void carregarAudio() {
    Audio& audio = obterAudio();

    audio.musica = LoadMusicStream(MUSICA_FUNDO);
    audio.botaoClick = LoadSound(BOTAO_CLICK);
    for (int i = 0; i < 2; i++) {
        audio.mouseSobre[i] = LoadSound(MOUSE_SOBRE);
    }
}

void descarregarAudio() {
    Audio& audio = obterAudio();

    UnloadMusicStream(audio.musica);
    UnloadSound(audio.botaoClick);
    for (int i = 0; i < 2; i++) {
        UnloadSound(audio.mouseSobre[i]);
    }
}

void tocarMusicaFundo() {
    Audio& audio = obterAudio();

    PlayMusicStream(audio.musica);
}

void manterMusicaTocando() {
    static const Audio& audio = obterAudio();

    UpdateMusicStream(audio.musica);
}

void carregarAudioJogo() {
    Audio& audio = obterAudio();

    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        audio.pecaClick[i] = LoadSound(PECAS_CLICK_SOM);
    }
    audio.vitoria = LoadSound(VITORIA_SOM);
}

void descarregarAudioJogo() {
    Audio& audio = obterAudio();

    for (int i = 0; i < TAM_PECAS_CLICK_ARR; i++) {
        UnloadSound(audio.pecaClick[i]);
    }
    UnloadSound(audio.vitoria);
}

void tocarPecaClick() {
    static const Audio& audio = obterAudio();
    static int i = 0;

    PlaySound(audio.pecaClick[i++]);
    if (i >= TAM_PECAS_CLICK_ARR) {
        i = 0;
    }
}

void tocarMouseSobre() {
    static const Audio& audio = obterAudio();
    static int i = 0;

    PlaySound(audio.mouseSobre[i++]);
    if (i >= 2) {
        i = 0;
    }
}

void tocarBotaoClick() {
    const Audio& audio = obterAudio();

    PlaySound(audio.botaoClick);
}

void tocarVitoria() {
    Audio& audio = obterAudio();

    PlaySound(audio.vitoria);
}
