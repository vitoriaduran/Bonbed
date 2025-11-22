#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "player.h"

Player *CriarPlayer() {
    Player *p = malloc(sizeof(Player));

    if (!p){
        return NULL;
    }
    
    p->vida_maxima = 100;
    p->vida_atual = 100;
    p->moedas = 150; //150 p/ testar a loja
    p->ataque = 10;
    p->chance_critica = 5; // 5% base

    p->dano_aplicado = 0;
    p->duracao_ataque = 0;
    p->armaHitbox = (Rectangle){0, 0, 40, 40};

    p->arma = LoadTexture("assets/sword.png");

    p->frameWidth  = 64;
    p->frameHeight = 64;
    p->estado_atual = ESTADO_IDLE;
    p->currentFrame = 0;
    p->contador_frames = 0;
    p->velocidade_frames = 6;
    p->MAX_frames = 4;

    p->pos = (Vector2){400, 300};
    p->velocidade = 240.0f;

    p->spritesheet = LoadTexture("assets/player.png");
    p->frameRec = (Rectangle){0, 0, p->frameWidth, p->frameHeight};

    return p;
}

void UpdatePlayer(Player *p) {
    
    if (p->vida_atual <= 0) {
        return;
    }

    Vector2 movimento = {0, 0};
    float dt = GetFrameTime();

    // Movimento é bloqueado se o ataque estiver ativo
    if (p->duracao_ataque == 0) {
        if (IsKeyDown(KEY_D)) movimento.x = 1;
        else if (IsKeyDown(KEY_A)) movimento.x = -1;

        if (IsKeyDown(KEY_S)) movimento.y = 1;
        else if (IsKeyDown(KEY_W)) movimento.y = -1;
    }
    
    // Aplica movimento
    if (movimento.x != 0 || movimento.y != 0) {
        movimento = Vector2Normalize(movimento);
        p->pos.x += movimento.x * p->velocidade * dt;
        p->pos.y += movimento.y * p->velocidade * dt;
    }

    // --- LÓGICA DE ESTADO E ANIMAÇÃO ---
    if (p->duracao_ataque > 0) {
        p->estado_atual = ESTADO_ATACANDO;
        p->duracao_ataque--; // Diminui a duração do ataque
        p->MAX_frames = 3; 
    } else if (movimento.x != 0 || movimento.y != 0) {
        // Estado de Andar
        p->MAX_frames = 4;

        if (fabs(movimento.y) > fabs(movimento.x)) {
            if (movimento.y < 0) p->estado_atual = ESTADO_WALK_UP;
            else p->estado_atual = ESTADO_WALK_DOWN;
        } else {
            if (movimento.x < 0) p->estado_atual = ESTADO_WALK_LEFT;
            else p->estado_atual = ESTADO_WALK_RIGHT;
        }
    } 
    else {
        // Estado IDLE
        p->estado_atual = ESTADO_IDLE;
        p->MAX_frames = 4; 
    }
    
    // --- CONTROLE DE FRAMES ---
    p->contador_frames++;

    if (p->contador_frames >= (60 / p->velocidade_frames)) {
        p->contador_frames = 0;
        p->currentFrame++;

        if (p->currentFrame >= p->MAX_frames) {
            p->currentFrame = 0;
        }
    }

    // Atualiza o recorte da sprite com base no estado e frame
    p->frameRec.x = (float)p->currentFrame * p->frameWidth;
    p->frameRec.y = (float)p->estado_atual * p->frameHeight;

    // --- ATAQUE (ATIVAÇÃO) ---
    if (IsKeyPressed(KEY_SPACE) && p->duracao_ataque == 0) {
        Ataque(p);
    }
    
    // Atualiza a hitbox da arma
    p->armaHitbox.x = p->pos.x + 30;
    p->armaHitbox.y = p->pos.y;
}

void Ataque(Player *p) {
    p->duracao_ataque = 15; // duração em frames (não alterar p->ataque!)
    p->currentFrame = 0;

    p->dano_aplicado = p->ataque;

    if (GetRandomValue(1, 100) <= p->chance_critica){
        p->dano_aplicado *= 2; //dobra o dano
    }
}

void Desenho_player(Player *p) {
    
    DrawTextureRec(
        p->spritesheet,
        p->frameRec,
        p->pos,
        WHITE
    );

    // Desenhar arma se estiver atacando
    if (p->duracao_ataque > 0) {
        DrawTextureV(
            p->arma,
            (Vector2){p->pos.x + 30, p->pos.y},
            WHITE
        );
        // hitbox acompanha o ataque
        p->armaHitbox.x = p->pos.x + 30;
        p->armaHitbox.y = p->pos.y;
    }
}

void Liberar_player(Player *p) {
    UnloadTexture(p->spritesheet);
    UnloadTexture(p->arma);
    free(p);
}