#include <raylib.h>
#include<game.h>

typedef struct protagonista{
    Vector2 position;
    Vector2 target_position;
    float speed;

    int vidas;
    int moedas;
    int forca;

    int frame_atual;
    int contador_frames;
    int loop_frames;
    int frames_por_loop;
    bool movimento;
} protagonista;





int main() {
   InitWindow(800, 600, "Bonded - MVP");
    InitAudioDevice();
    SetTargetFPS(60);

    Game *game = InitGame();

    while (!WindowShouldClose()) {
        UpdateGame(game);

        if (game -> gameOver && IsKeyPressed(KEY_ENTER)){
            
        if (game->gameOver && IsKeyPressed(KEY_ENTER)) {
            Liberar_Game(game);
            game = InitGame();
        }

        BeginDrawing();
        Desenho_Game(game);
        EndDrawing();
    }

    Liberar_Game(game);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

