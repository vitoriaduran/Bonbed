#ifndef LOJA_H
#define LOJA_H

#include "raylib.h"
#include "player.h" // Necessário para aplicar upgrades

// Tipos de Itens para a loja
typedef enum {
    ITEM_VIDA_MAX,
    ITEM_DANO,
    ITEM_VELOCIDADE,
    ITEM_CRITICO
} TipoItem;

// Estrutura para definir cada item da loja
typedef struct {
    TipoItem tipo;
    char nome[50];
    char descricao[100];
    int preco;
    int valor_upgrade; // Valor que será adicionado/modificado
} ItemLoja;

// Variável global para armazenar o catálogo de itens
// O array de itens deve ser definido e preenchido em loja.c
#define MAX_ITENS 4 
extern ItemLoja catalogo[MAX_ITENS]; // extern indica que a variável está definida em loja.c

// Funções do Módulo Loja
void inicializar_loja();
void atualizar_loja(Player *player, int *itemSelecionado);
void desenhar_loja(int itemSelecionado, Player *player);
 
#endif 