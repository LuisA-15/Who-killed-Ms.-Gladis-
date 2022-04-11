#include "raylib.h"
#include <stdio.h>

typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
    int state; // 1 if pressed down, 0 if not
}Button;


void MainWindow();
void AboutWindow();


void MainWindow()
{
    InitWindow(600, 500, "Who killed Ms. Gladis?");
    Vector2 mousePoint;

    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TRed = LoadTexture("../Assets/redSheet.png");

    Button start = {
            TBlue,
            {225, 200},
            {0,94,190, 49},
            {start.position.x, start.position.y, start.mask.width, start.mask.height},
            0
    };
    Button about = {
            TBlue,
            {225, 260},
            {0,94,190, 49},
            {about.position.x, about.position.y, about.mask.width, about.mask.height},
            0
    };
    Button exit = {
            TRed,
            {225, 330},
            {190, 0, 190, 49},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});

        DrawText("Who Killed Ms. Gladis?", 25, 100, 50, BLACK);

        DrawTextureRec(start.texture, start.mask, start.position, WHITE);
        DrawText("Jugar", 280, 205, 30, BLACK);
        DrawTextureRec(about.texture, about.mask, about.position, WHITE);
        DrawText("Acerca de", 240, 270, 30, BLACK);
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
        DrawText("Salir", 290, 340, 30, BLACK);

        mousePoint = GetMousePosition();

        if (IsMouseButtonPressed(0))
        {
            if (IsMouseButtonDown(0))
            {
                if (CheckCollisionPointRec(mousePoint, start.collision))
                {
                    start.texture = TYellow;
                    start.mask = (Rectangle) {0, 50, 190, 45};
                    start.state = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, about.collision))
                {
                    about.texture = TYellow;
                    about.mask = (Rectangle) {0, 50, 190, 45};
                    about.state = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, exit.collision))
                {
                    exit.mask = (Rectangle) {0, 0, 190, 45};
                    exit.state = 1;
                }
            }
        }

        if (IsMouseButtonReleased(0))
        {
            if (CheckCollisionPointRec(mousePoint, start.collision))
            {
                if(start.state)
                {
                    ClearBackground(RED);
                }
            }
            else if (CheckCollisionPointRec(mousePoint, about.collision))
            {
                if (about.state)
                {
                    EndDrawing();
                    break;
                }
            }
            else if (CheckCollisionPointRec(mousePoint, exit.collision))
            {
                if (exit.state)
                {
                    EndDrawing();
                    break;
                }
            }

            start.texture = TBlue;
            start.mask = (Rectangle) {0,94,190, 49};
            start.state = 0;
            about.texture = TBlue;
            about.mask = (Rectangle) {0, 94, 190, 49};
            about.state = 0;
            exit.mask = (Rectangle) {190, 0 , 190, 49};
            exit.state = 0;

        }
        EndDrawing();
    }
    CloseWindow();
    if (about.state)
    {
        AboutWindow();
    }
}

void AboutWindow()
{
    InitWindow(400, 500, "Acerca de");
    Vector2 mousePoint;

    Texture2D TRed = LoadTexture("../Assets/redsheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");

    Button exit = {
            TGrey,
            {350, 450},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

        mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, exit.collision))
        {
            exit.texture = TRed;
            exit.mask = (Rectangle) {381, 36, 36, 36};
            if (IsMouseButtonPressed(0))
            {
                EndDrawing();
                break;
            }
        }
        else
        {
            exit.texture = TGrey;
            exit.mask = (Rectangle) {186, 433, 36, 36};
        }

        EndDrawing();
    }
    CloseWindow();
    MainWindow();
}