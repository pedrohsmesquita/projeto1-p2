#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

#define PECAS_CLICK_SOM "assets/sounds/pecas_click.wav"
#define MUSICA_FUNDO "assets/sounds/bg_music.mp3"
#define TAM_PECAS_CLICK_ARR 6

struct Audio {
    Music musica;
    Sound pecaClick[TAM_PECAS_CLICK_ARR];
};

void carregaAudio();
void descarregarAudio();
void tocarMusicaFundo();
void manterMusicaTocando();
void carregarPecasAudio();
void descarregarPecasAudio();
void tocarPecaClick();

#endif // AUDIO_H
