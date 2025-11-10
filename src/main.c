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
<<<<<<< HEAD
<<<<<<< HEAD
   InitWindow(800, 600, "Bonded - MVP");
=======
    InitWindow(800, 600, "Bonded - MVP");
>>>>>>> c1ac3d3 (Junção dos últimos 2 commits)
=======
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Bonded - MVP");
>>>>>>> d94deb3 (Sisteminha de movimentação que será substituído pelo sprite do protagonista)
    InitAudioDevice();
    SetTargetFPS(60);

    Vector2  = { (float)screenWidth/2, (float)screenHeight/2 }
    
    Game *game = InitGame();

    while (!WindowShouldClose()) {
        UpdateGame(game);

        if (game -> gameOver && IsKeyPressed(KEY_ENTER)){

        if (game->gameOver && IsKeyPressed(KEY_ENTER)) {
            Liberar_Game(game);
            game = InitGame();
        }

        if (IsKeyDown(KEY_RIGHT)) posicao_protagonista.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) posicao_protagonista.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) posicao_protagonista.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) posicao_protagonista.y += 2.0f;

        BeginDrawing();
        Desenho_Game(game);
        DrawCircleV(posicao_protagonista, 50, RED);
        EndDrawing();
    }

    Liberar_Game(game);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

