#include "inimigo.h"
#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

Inimigo *Criar_inimigo(float x, float y) {
    Inimigo *novo = malloc(sizeof(Inimigo));
    if (!novo){
         return NULL;
    }

    novo->pos = (Vector2){ x, y };
    novo->velocidade = 2.0f;
    novo->hp = 3;
    novo->sprite = LoadTexture("assets/enemy.png");
    novo->next = NULL;

    return novo;
}

void mov_inimigos(Inimigo *head, Vector2 playerPos) {
    for (Inimigo *novo = head; novo != NULL; novo = novo->next) {

        Vector2 dir = { playerPos.x - novo->pos.x, playerPos.y - novo->pos.y };
        float len = sqrtf(dir.x * dir.x + dir.y * dir.y);

        if (len > 0) {
            dir.x /= len;
            dir.y /= len;
        }

        novo->pos.x += dir.x * novo->velocidade;
        novo->pos.y += dir.y * novo->velocidade;
    }
}

void Desenho_inimigos(Inimigo *head) {
    for (Inimigo *novo = head; novo != NULL; novo = novo->next) {
        DrawTexture(novo->sprite, novo->pos.x, novo->pos.y, WHITE);
    }
}

void Liberar_memoria(Inimigo *head) {
    while (head != NULL) {
        Inimigo *tmp = head;
        head = head->next;
        UnloadTexture(tmp->sprite);
        free(tmp);
    }
}

void add_inimigo(Inimigo **head) {
    Inimigo *novo = Criar_inimigo(
        GetRandomValue(100, 700),
        GetRandomValue(100, 400)
    );

    if (!novo) return;

    novo->next = *head;
    *head = novo;
}

void Colisao(Player *player, Inimigo **inimigos, int *moedas) {
    Inimigo *prev = NULL;
    Inimigo *curr = *inimigos;

    while (curr != NULL) {

        Rectangle playerRect = {
            player->pos.x,
            player->pos.y,
            (float)player->frameWidth,
            (float)player->frameHeight
        };

        Rectangle enemyRect = {
            curr->pos.x,
            curr->pos.y,
            (float)curr->sprite.width,
            (float)curr->sprite.height
        };

        if (CheckCollisionRecs(playerRect, enemyRect)) {

            player-> vida_atual -= 1;
            (*moedas)++;

            if (prev == NULL) {
                *inimigos = curr->next;
                UnloadTexture(curr->sprite);
                free(curr);
                curr = *inimigos;
            } else {
                prev->next = curr->next;
                UnloadTexture(curr->sprite);
                free(curr);
                curr = prev->next;
            }

        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}
