#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

#define PECAS_CLICK_SOM "assets/sounds/pecas_click.wav"
#define MUSICA_FUNDO "assets/sounds/bg_music.mp3"
#define VITORIA_SOM "assets/sounds/vitoria.wav"
#define MOUSE_SOBRE "assets/sounds/mouse_hover.ogg"
#define BOTAO_CLICK "assets/sounds/botao_click.wav"
#define SALVAR_SUCESSO "assets/sounds/salvar_sucesso.wav"
#define SALVAR_FALHA "assets/sounds/salvar_falha.ogg"
#define TAM_PECAS_CLICK_ARR 6

struct Audio {
    Music musica;
    Sound pecaClick[TAM_PECAS_CLICK_ARR];
    Sound vitoria;
    Sound mouseSobre[2];
    Sound botaoClick;
    Sound salvarSucesso;
    Sound salvarFalha;
};

void carregarAudio();
void descarregarAudio();
void tocarMusicaFundo();
void manterMusicaTocando();
void carregarAudioJogo();
void descarregarAudioJogo();
void carregarAudioCustomizar();
void descarregarAudioCustomizar();
void tocarPecaClick();
void tocarMouseSobre();
void tocarBotaoClick();
void tocarVitoria();
void tocarSalvarSucesso();
void tocarSalvarFalha();

#endif // AUDIO_H
