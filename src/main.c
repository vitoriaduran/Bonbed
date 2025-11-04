#include "raylib.h"

int main() {
    InitWindow(800, 450, "Meu Jogo");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib funcionando!", 280, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

