#include <raylib.h>

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


    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Bonded - MVP");

    InitAudioDevice();
    SetTargetFPS(60);

    
    protagonista player = {
        .position = { screenWidth/2.0f, screenHeight/2.0f },
        .speed = 2.0f,
        .vidas = 3,
        .moedas = 0,
        .forca = 1,
        .frame_atual = 0,
        .contador_frames = 0,
        .loop_frames = 4,
        .frames_por_loop = 8,
        .movimento = false
    };

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_RIGHT)) player.position.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) player.position.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) player.position.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) player.position.y += 2.0f;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bonded - MVP", 10, 10, 20, BLACK);
        DrawCircleV(player.position, 50, RED);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
} 

