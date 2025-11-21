#include "fases.h"
#include <stdlib.h>
#include "raylib.h"

//falta a logica das novas fases que esta no grupo
Fase *CarregarFase(int id) {
    Fase *fase = malloc(sizeof(Fase));
    fase->id = id;
    fase->concluida = false;

    // Carrega o fundo da fase
    if (id == 1) {
        fase->background = LoadTexture("assets/backgrounds/floresta.png");
        fase->playerStart = (Vector2){100, 300};

        // Cria alguns inimigos na floresta
        Inimigo *novo1 = Criar_inimigo(400, 300);
        Inimigo *novo2 = Criar_inimigo(600, 200);
        novo1->next = novo2;
        fase->inimigos = novo1;
    }
    else if (id == 2) {
        fase->background = LoadTexture("assets/backgrounds/caverna.png"); //falta sprint
        fase->playerStart = (Vector2){80, 350};

        Inimigo *novo1 = Criar_inimigo(500, 250);
        fase->inimigos = novo1;
    }
    else {
        fase->background = LoadTexture("assets/backgrounds/default.png"); //falta sprint
        fase->playerStart = (Vector2){50, 50};
        fase->inimigos = NULL;
    }

    return fase;
}

void AtualizarFase(Fase *fase, Vector2 playerPos, bool is_attacking) {
    if (fase == NULL){
        return;

    }
    // Define se a fase atual é de combate (não é a Loja)
    bool fase_combate = ( fase->id != 2);

    if (fase_combate) {
        // (Isso evita que inimigos ataquem durante a animação de ataque/cooldown do jogador)
        if (!is_attacking) {

            mov_inimigos(fase->inimigos, playerPos); 
        }
    }

    if (fase_combate) {
    
        // A fase está concluída se a lista de inimigos estiver vazia.
        if (fase->inimigos == NULL) {
            fase->concluida = true;
        }

    } else {
        // Condição para fases de PASSAGEM (Ex: Loja, id=2):
        // A fase está concluída se o jogador atingir a área de saída (lado direito da tela).
        
        if (playerPos.x > 750) { 

            fase->concluida = true;
        }
    }
}

void DesenharFase(Fase *fase, int ItemSelecionado, Player *player) {
    if (fase == NULL){
        return;

    } 

    // Desenha o fundo
    DrawTexture(fase->background, 0, 0, WHITE);

    // Desenha inimigos
    Desenho_inimigos(fase->inimigos);
}

void LiberarFase(Fase *fase) {
    if (fase == NULL) return;

    UnloadTexture(fase->background);
    Liberar_memoria(fase->inimigos);
    free(fase);
}
