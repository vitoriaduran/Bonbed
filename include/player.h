#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"

typedef enum
{
    ESTADO_IDLE = 0,
    ESTADO_WALK_UP,
    ESTADO_WALK_LEFT,
    ESTADO_WALK_RIGHT,
    ESTADO_WALK_DOWN,
    ESTADO_ATACANDO //Novo estado p/ controlar a animaçao
}PlayerState;

typedef struct {
    Vector2 pos;
    float velocidade;

    int vida_maxima;
    int vida_atual;
    int moedas;
    int ataque;
    int chance_critica;

    int dano_aplicado;
    int duracao_ataque;
    Rectangle armaHitbox;
    Texture2D arma;

    Texture2D spritesheet; 
    Rectangle frameRec;      // Recorte da sprite atual
    int frameWidth;          // Largura de um único frame
    int frameHeight;         // Altura de um único frame
    PlayerState estado_atual; // Estado atual do player (IDLE, WALK, etc.)
    int currentFrame;        // Frame atual da animação
    int contador_frames;     // Contador para controle de velocidade da animação
    int velocidade_frames;   // FPS da animação
    int MAX_frames;          // Máximo de frames para o estado atual

} Player;

Player *CriarPlayer();
void UpdatePlayer(Player *p);
void Desenho_player(Player *p);
void Ataque(Player *p);
void Liberar_player(Player *p);

#endif

