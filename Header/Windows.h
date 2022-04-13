#include "raylib.h"
#include <stdio.h>

typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
    int status; // 1 if pressed down, 0 if not
}Button;

enum texture_names {
    TBLUE,
    TYELLOW,
    TRED,
    TGREEN,
    TGREY
};


void MainWindow();
void AboutWindow(Texture2D textures[]);
void ChoosePlayers(Texture2D textures[]);
void HowtoPlayWindow(Texture2D textures[]);


void MainWindow()
{
    InitWindow(600, 500, "Who killed Ms. Gladis?");
    Vector2 mousePoint;

    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TRed = LoadTexture("../Assets/redSheet.png");
    Texture2D TGreen = LoadTexture("../Assets/greenSheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");
    Texture2D guiTextures[] = {TBlue, TYellow, TRed, TGreen, TGrey};

    Button start = {
            TBlue,
            {225, 200},
            {0,94,190, 49},
            {start.position.x, start.position.y, start.mask.width, start.mask.height},
            0
    };
    Button how = {
            TBlue,
            {225, 260},
            {0, 94,190, 49},
            {how.position.x, how.position.y, how.mask.width, how.mask.height},
            0
    };
    Button about = {
            TGreen,
            {225, 330},
            {0, 0,190, 49},
            {about.position.x, about.position.y, about.mask.width, about.mask.height},
            0
    };
    Button exit = {
            TRed,
            {225, 390},
            {190, 0, 190, 49},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };


    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});

        DrawText("Who Killed Ms. Gladis?", 25, 100, 50, BLACK);

        DrawTextureRec(start.texture, start.mask, start.position, WHITE);
        DrawText("Jugar", 280, 205, 30, BLACK);
        DrawTextureRec(how.texture, how.mask, how.position, WHITE);
        DrawText("Cómo Jugar", 235, 270, 30, BLACK);
        DrawTextureRec(about.texture, about.mask, about.position, WHITE);
        DrawText("Acerca de", 240, 340, 30, BLACK);
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
        DrawText("Salir", 290, 400, 30, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePoint, start.collision))
                {
                    start.texture = TYellow;
                    start.mask = (Rectangle) {0, 50, 190, 45};
                    start.status = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, how.collision))
                {
                    how.texture = TYellow;
                    how.mask = (Rectangle) {0, 50, 190, 45};
                    how.status = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, about.collision))
                {
                    about.mask = (Rectangle) {0, 192, 190, 45};
                    about.status = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, exit.collision))
                {
                    exit.mask = (Rectangle) {0, 0, 190, 45};
                    exit.status = 1;
                }
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePoint, start.collision))
            {
                if (start.status)
                {
                    EndDrawing();
                    ChoosePlayers(guiTextures);
                }
            }
            else if (CheckCollisionPointRec(mousePoint, how.collision))
            {
                if (how.status)
                {
                    EndDrawing();
                    HowtoPlayWindow(guiTextures);
                }
            }
            else if (CheckCollisionPointRec(mousePoint, about.collision))
            {
                if (about.status)
                {
                    EndDrawing();
                    AboutWindow(guiTextures);
                }
            }
            else if (CheckCollisionPointRec(mousePoint, exit.collision))
            {
                if (exit.status)
                {
                    EndDrawing();
                    break;
                }
            }

            start.texture = TBlue;
            start.mask = (Rectangle) {0,94,190, 49};
            start.status = 0;

            how.texture = TBlue;
            how.mask = (Rectangle) {0, 94, 190, 49};
            how.status = 0;

            about.texture = TGreen;
            about.mask = (Rectangle) {0, 0, 190, 49};
            about.status = 0;

            exit.mask = (Rectangle) {190, 0 , 190, 49};

        }
        EndDrawing();
    }
    CloseWindow();
}

void ChoosePlayers(Texture2D textures[])
{
    SetWindowSize(700, 500);
    Vector2 mousePoint;

//    Button threePlayers;
//    Button fourPlayers;
    Button changePlayer = {
            textures[TGREY],
            {0, 0},
            {223, 433, 36, 36},
            {0, 0},
            0,
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTextureRec(changePlayer.texture, changePlayer.mask, changePlayer.position, WHITE);
        EndDrawing();
    }
    SetWindowSize(600, 500);
}

void HowtoPlayWindow(Texture2D textures[]) {
    SetWindowTitle("Cómo Jugar");
    Vector2 mousePoint;
    Button exit = {
            textures[TGREY],
            {550, 450},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };

    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

        if (CheckCollisionPointRec(mousePoint, exit.collision)) {
            exit.texture = textures[TRED];
            exit.mask = (Rectangle) {381, 36, 36, 36};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                EndDrawing();
                break;
            }
        }
        else
        {
            exit.texture = textures[4];
            exit.mask = (Rectangle) {186, 433, 36, 35};
        }

        EndDrawing();
    }
}

void AboutWindow(Texture2D textures[])
{
    SetWindowTitle("Acerca de");
    Vector2 mousePoint;
    Button exit = {
            textures[TGREY],
            {550, 450},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };

    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

        if (CheckCollisionPointRec(mousePoint, exit.collision)) {
            exit.texture = textures[TRED];
            exit.mask = (Rectangle) {381, 36, 36, 36};
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                EndDrawing();
                break;
            }
        }
        else
        {
            exit.texture = textures[4];
            exit.mask = (Rectangle) {186, 433, 36, 35};
        }

        EndDrawing();
    }
}