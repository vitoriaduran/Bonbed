#include "player.h"
#include <stdlib.h>
#include <math.h>

Player *CriarPlayer() { // se quiser que o personagem aparece em outra pos, adcionar parametros
    Player *p = malloc(sizeof(Player));

    p->spritesheet = LoadTexture("resources/player_spritesheetpng");

    p->frameWidth = 360;
    p->frameHeight = 360;

    p->estadoAtual = IDLE;
    p->currentFrame = 0;
    p->contador_frames = 0;
    p->velocidade_frames = 5;
    p->MAX_frames = 4;

    p -> pos = (Vector2){400, 300};
    p -> velocidade = 4.0f;
    p -> hp = 5;
    p -> sprite = LoadTexture("assets/player.png"); //falta colocar
    p -> arma = LoadTexture("assets/sword.png"); //falta colocar 
    p -> ataque = 0;
    p ->armaHitbox = (Rectangle){p->pos.x, p->pos.y, 40, 40};

    p->frameRec = (Rectangle){0.0f, 0.0f, (float)p->frameWidth, (float)p->frameHeight};
    return p;
}


void UpdatePlayer(Player *p) {
    Vetor2 movimento = {0.0f,0.0f};

    if (IsKeyDown(KEY_RIGHT)) movimento.x = 1.0f;
    else if (IsKeyDown(KEY_LEFT)) movimento.x = -1.0f;

    if (IsKeyDown(KEY_S)) movimento.y = 1.0f;
    else if (IsKeyDown(KEY_W)) movimento.y = -1.0f;

    if (movimento.x != 0.0f || movimento.y != 0.0f) {
        movimento = Vector2Normalize(movimento);
        p->pos.x += movimento.x * p->velocidade * GetFrameTime();
        p->pos.y += movimento.y * p->velocidade * GetFrameTime();
    }
    float stateY = 0.0f;
    if (movimento.x != 0.0f || movimento.y != 0.0f) {
        p->estadoAtual = WALK_DOWN; 
        p->maxFrames = 4;

        if (fabs(movimento.y) > fabs(movimento.x)){
            if (movimento.y <0.0f) stateY = 1.0f;
            else stateY =0.0f;
        }else{
            if (movimento.x < 0.0f) stateY = 2.0f;
            else stateY = 3.0f;
        }

    }else{
        p->estadoAtual = IDLE;
        p->MAX_frames = 4;
        stateY = 0.0f;
    }

    p->contador_frames++;

    if (p->contador_frames >= (60/p->velocidade_frames)) {
        p->contador_frames = 0;
        p->currentFrame++;
        
        if (p->currentFrame >= p->MAX_frames) {
            p->currentFrame = 0;
        }
    }
    p->frameRec.x = (float)p->currentFrame * p->frameWidth;
    p->frameRec.y = stateY * p->frameHeight;

    if (IsKeyPressed(KEY_SPACE)) Ataque(p);
}
}

void Ataque(Player *p) {
    p -> ataque= 1;
    p -> armaHitbox = (Rectangle){p->pos.x + 20, p->pos.y, 40, 40};
}

void Desenho_player(Player *p) {
    DrawTexture(
        p->spritesheet,
        p->frameRec,
        p->pos,
        WHITE
    );
    
    if (p -> ataque) {
        DrawTexture(p -> arma, p->pos.x + 30, p->pos.y, WHITE);
        p -> ataque = 0;
    }
}

void Liberar_player(Player *p) {
    UnloadTexture(p -> sprite);
    UnloadTexture(p -> arma);
    free(p);
}
