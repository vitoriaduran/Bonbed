#ifndef FASES_H
#define FASES_H

#include "raylib.h"
#include "inimigo.h"

// Estrutura de uma fase
typedef struct Fase {
    int id;                     // Número da fase
    Texture2D background;       // Fundo da fase
    Inimigo *inimigos;            // Lista encadeada de inimigos
    Vector2 playerStart;        // Posição inicial do jogador
    bool concluida;             // Se o jogador terminou a fase
} Fase;

// Funções principais
Fase *CarregarFase(int id);
void AtualizarFase(Fase *fase, Vector2 playerPos, bool is_attacking);
void DesenharFase(Fase *fase, int itemSelecionado, Player *player);
void LiberarFase(Fase *fase);

#endif

