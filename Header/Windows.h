#include "raylib.h"

typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
    int state; // 1 if pressed down, 0 if not
}Button;

void MainWindow();


void MainWindow()
{
    InitWindow(600, 500, "Who killed Ms. Gladis?");
    Vector2 mousePoint;

    Texture2D TBLUE = LoadTexture("../Assets/blueSheet.png");
    Texture2D TYELLOW = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TRED = LoadTexture("../Assets/redSheet.png");

    Button start = {
            TBLUE,
            {225, 200},
            {0,94,190, 49},
            {start.position.x, start.position.y, start.mask.width, start.mask.height},
            0
    };
    Button about = {
            TBLUE,
            {225, 260},
            {0,94,190, 49},
            {about.position.x, about.position.y, about.mask.width, about.mask.height},
            0
    };
    Button exit = {
            TRED,
            {225, 330},
            {190, 0, 190, 49},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

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
                    start.texture = TYELLOW;
                    start.mask = (Rectangle) {0, 50, 190, 45};
                    start.state = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, about.collision))
                {
                    about.texture = TYELLOW;
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
                    ClearBackground(VIOLET);
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

            start.texture = TBLUE;
            start.mask = (Rectangle) {0,94,190, 49};
            start.state = 0;
            about.texture = TBLUE;
            about.mask = (Rectangle) {0, 94, 190, 49};
            about.state = 0;
            exit.mask = (Rectangle) {190, 0 , 190, 49};
            exit.state = 0;

        }
        EndDrawing();
    }
    CloseWindow();
}