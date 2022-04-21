#include <stdio.h>
#include "raylib.h"

int main() {
    const int screenWidth = 700;
    const int screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "Who killed Mrs. Gladys?");
    SetTargetFPS(30);
    Image room1 = LoadImage("../Assets/Tileset_16x16_1-mod.png");
    Image room2 = LoadImage("../Assets/Tileset_16x16_2.png");
    Image room3 = LoadImage("../Assets/Tileset_16x16_3.png");
    Image room4 = LoadImage("../Assets/Tileset_16x16_4.png");
    Image room5 = LoadImage("../Assets/Tileset_16x16_5.png");
    Image floor = LoadImage("../Assets/complete_floor2.png");
    Image floor_base = LoadImage("../Assets/floor.png");
    Image carpet = LoadImage("../Assets/complete_carpet.png");
    Image garden = LoadImage("../Assets/GARDEN.png");

    Texture room1Texture = LoadTextureFromImage(room1);
    Texture room2Texture = LoadTextureFromImage(room2);
    Texture room3Texture = LoadTextureFromImage(room3);
    Texture room4Texture = LoadTextureFromImage(room4);
    Texture room5Texture = LoadTextureFromImage(room5);
    Texture roomFloor = LoadTextureFromImage(floor);
    Texture roomFloor2 = LoadTextureFromImage(floor_base);
    Texture carpetTexture = LoadTextureFromImage(carpet);
    Texture Garden = LoadTextureFromImage(garden);


    UnloadImage(room1); UnloadImage(room2); UnloadImage(room3); UnloadImage(room4);
    UnloadImage(room5); UnloadImage(floor); UnloadImage(floor_base); UnloadImage(carpet);
    UnloadImage(garden);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKBROWN);
        DrawTexture(Garden, screenWidth/7+15, 10, RAYWHITE);
        DrawTexture(Garden, screenWidth/7*5 -45, 10, RAYWHITE);
        DrawTexture(Garden, screenWidth/7, screenHeight/8*6-15, RAYWHITE);
        DrawTexture(Garden, screenWidth/7*5-50, screenHeight/8*6-15, RAYWHITE);
        DrawTexture(room2Texture, screenWidth/2-70, 18, RAYWHITE);
        DrawTexture(room4Texture, screenWidth/7+1,screenHeight/8*2 + 10, RAYWHITE);
        DrawTexture(room5Texture, screenWidth/7*5-51,  screenHeight/8*2 +10, RAYWHITE);
        DrawTexture(room1Texture, screenWidth/7+14 , screenHeight/8*4, RAYWHITE);
        DrawTexture(room3Texture, screenWidth/7*5-51, screenHeight/8*4, RAYWHITE);
        //DrawRectangleLines(screenWidth/3+28, screenHeight/4-15, roomFloor.width, roomFloor2.height, BLACK);
        DrawTexture(roomFloor, screenWidth/3+28, screenHeight/4, RAYWHITE);
        DrawTexture(carpetTexture, screenWidth/3+30 + roomFloor2.width, screenHeight/4 + roomFloor2.height*3, RAYWHITE);

        EndDrawing();
    }
    CloseWindow();

    printf("Hello, World!\n");
    return 0;
}

