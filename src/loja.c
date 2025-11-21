#include "loja.h"
#include <stdio.h>
#include <string.h>

// Definição da variável global do catálogo
ItemLoja catalogo[MAX_ITENS]; 

void inicializar_loja() {
    // --- ITEM 1: VIDA MÁXIMA ---
    catalogo[0].tipo = ITEM_VIDA_MAX;
    strcpy(catalogo[0].nome, "Poção Vital");
    strcpy(catalogo[0].descricao, "Aumenta a Vida Máxima em 25.");
    catalogo[0].preco = 100;
    catalogo[0].valor_upgrade = 25;

    // --- ITEM 2: DANO BASE ---
    catalogo[1].tipo = ITEM_DANO;
    strcpy(catalogo[1].nome, "Lâmina Afiada");
    strcpy(catalogo[1].descricao, "Aumenta o Dano Base em 10.");
    catalogo[1].preco = 150;
    catalogo[1].valor_upgrade = 10;
    
    // --- ITEM 3: VELOCIDADE ---
    catalogo[2].tipo = ITEM_VELOCIDADE;
    strcpy(catalogo[2].nome, "Bota de velocidade");
    strcpy(catalogo[2].descricao, "Aumenta a Velocidade em 50 px/s.");
    catalogo[2].preco = 120;
    catalogo[2].valor_upgrade = 50;

    // --- ITEM 4: CHANCE CRÍTICA ---
    catalogo[3].tipo = ITEM_CRITICO;
    strcpy(catalogo[3].nome, "Amuleto da Sorte");
    strcpy(catalogo[3].descricao, "Aumenta a Chance Crítica em 5%");
    catalogo[3].preco = 200;
    catalogo[3].valor_upgrade = 5; // Representa 5%
}

// Lógica para navegação e compra na loja
void atualizar_loja(Player *player, int *itemSelecionado) {
    // Navegação (Mudar o item selecionado)
    if (IsKeyPressed(KEY_RIGHT) && *itemSelecionado < MAX_ITENS - 1) {
        (*itemSelecionado)++;
    }
    if (IsKeyPressed(KEY_LEFT) && *itemSelecionado > 0) {
        (*itemSelecionado)--;
    }

    // Tentativa de Compra
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
        ItemLoja item = catalogo[*itemSelecionado];

        if (player->moedas >= item.preco) {
            // Efetua a compra
            player->moedas -= item.preco;

            // Aplica o Upgrade
            switch (item.tipo) {
                case ITEM_VIDA_MAX:
                    player->vida_maxima += item.valor_upgrade;
                    player->vida_atual += item.valor_upgrade; // Cura total ao comprar HP
                    break;

                case ITEM_DANO:
                    player->ataque += item.valor_upgrade;
                    break;

                case ITEM_VELOCIDADE:
                    player->velocidade += (float)item.valor_upgrade;
                    break;

                case ITEM_CRITICO:
                    if (player->chance_critica + item.valor_upgrade <= 100) {
                         player->chance_critica += item.valor_upgrade;

                    } else {

                         player->chance_critica = 100;

                    }

                    break;
            }
            
            
            DrawText("COMPRA REALIZADA!", 300, 300, 40, GREEN);
            
        } else {
            
            DrawText("MOEDAS INSUFICIENTES!", 300, 300, 40, RED);
            
        }
    }
}

// Desenho da interface da loja
void desenhar_loja(int itemSelecionado, Player *player) {
    int baseX = 50;
    int baseY = 150;
    int spacing = 180;
    
    DrawText("🛍️ LOJA DE UPGRADES 🛍️", 250, 50, 30, YELLOW);
    
    // Desenha todos os itens
    for (int i = 0; i < MAX_ITENS; i++) {
        ItemLoja item = catalogo[i];
        int x = baseX + i * spacing;

        // Desenha a caixa do item
        Color boxColor = (i == itemSelecionado) ? SKYBLUE : DARKGRAY;
        DrawRectangle(x, baseY, 150, 250, boxColor);
        DrawRectangleLines(x, baseY, 150, 250, BLACK);

        // Informações do Item
        DrawText(item.nome, x + 10, baseY + 10, 20, RAYWHITE);
        DrawText(TextFormat("Preço: %d", item.preco), x + 10, baseY + 200, 18, GOLD);
        DrawText(item.descricao, x + 10, baseY + 40, 15, RAYWHITE);
        DrawText(TextFormat("+%d", item.valor_upgrade), x + 10, baseY + 170, 20, LIME);
    }
    
    // Desenha instruções
    DrawText("Use SETAS ESQ/DIR para navegar. Pressione ESPAÇO para comprar.", 150, 450, 20, WHITE);
    
    // Desenha o status do jogador (para referência)
    DrawText(TextFormat("Suas Moedas: %d", player->moedas), 50, 50, 20, GOLD);
    DrawText(TextFormat("HP Max: %d", player->vida_maxima), 50, 80, 20, RED);
    DrawText(TextFormat("Dano: %d", player->ataque), 50, 110, 20, MAROON);
} 