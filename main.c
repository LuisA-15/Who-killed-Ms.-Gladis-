#include "raylib.h"

int main() {
    InitWindow(600, 500, "Clue Sus");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}