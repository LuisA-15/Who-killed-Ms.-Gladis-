#include "raylib.h"
#include <stdio.h>

typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
    int status; // 2 if disabled, 1 if pressed, 0 if not
} Button;

typedef struct picture_struct {
    Texture2D texture;
    Rectangle mask;
    Rectangle resize;
} Picture;

enum texture_names {
    TBLUE,
    TYELLOW,
    TRED,
    TGREEN,
    TGREY
};

char names[][15] = {
        "Ms. Gladis",
        "El Coronel",
        "F",
        "Kim",
        "La abuela",
        "Hilda",
        ""
};


void MainWindow();
void AboutWindow(Texture2D textures[]);
void ChoosePlayers(Texture2D textures[]);
void HowtoPlayWindow(Texture2D textures[]);
int ChangeCharacter(int namesInUse[4], int actualName);


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
    SetWindowSize(700, 600);
    Vector2 mousePoint;
    int playerCount = 4;
    enum playerNames {
        REDNAME,
        BLUENAME,
        GREENNAME,
        YELLOWNAME
    };
    int playerNames[] = {0, 1, 2, 3};

    Texture2D circleArrows = LoadTexture("../Assets/changePlayer.png");

    Button exit = {
            textures[TGREY],
            {654, 554},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };
    Button ready = {
            textures[TGREEN],
            {245, 541},
            {0, 0,190, 49},
            {ready.position.x, ready.position.y, ready.mask.width, ready.mask.height},
            0
    };
    Button threePlayers = {
            textures[TGREY],
            {250, 30},
            {185, 469, 36, 36},
            {threePlayers.position.x, threePlayers.position.y, threePlayers.mask.width, threePlayers.mask.height},
            0
    };
    Button fourPlayers = {
            textures[TGREY],
            {350, 30},
            {185, 469, 36, 36},
            {fourPlayers.position.x, fourPlayers.position.y, fourPlayers.mask.width, fourPlayers.mask.height},
            1
    };
    Button changePlayer = {
            circleArrows,
            {0, 0},
            {0, 0, 36, 36},
            {0, 0, 36, 36},
            0,
    };
    Picture redPlayer = {
        textures[TRED],
        {337, 188, 49, 49},
        {110, 95, redPlayer.mask.width * 3, redPlayer.mask.height * 3},
    };
    Picture bluePlayer = {
        textures[TBLUE],
        {288, 194, 49, 49},
        {420, 95, bluePlayer.mask.width * 3, bluePlayer.mask.height * 3}
    };
    Picture greenPlayer = {
        textures[TGREEN],
        {337, 184, 49, 49},
        {110, 325, greenPlayer.mask.height * 3, greenPlayer.mask.height * 3}
    };
    Picture yellowPlayer = {
        textures[TYELLOW],
        {190, 194, 49, 49},
        {420, 325, yellowPlayer.mask.width * 3, yellowPlayer.mask.height * 3}
    };
    Picture nameHolder = {
            textures[TGREY],
            {2, 51, 186, 45}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});

        mousePoint = GetMousePosition();

        if (fourPlayers.status)
        {
            fourPlayers.texture = textures[TBLUE];
            fourPlayers.mask = (Rectangle) {386, 210, 36, 36};
            threePlayers.texture = textures[TGREY];
            threePlayers.mask = (Rectangle) {185, 469, 36, 36};

            yellowPlayer.texture = textures[TYELLOW];
            yellowPlayer.mask = (Rectangle) {190, 194, 49, 49};
        }
        else if (threePlayers.status) {
            threePlayers.texture = textures[TBLUE];
            threePlayers.mask = (Rectangle) {386, 210, 36, 36};
            fourPlayers.texture = textures[TGREY];
            fourPlayers.mask = (Rectangle) {185, 469, 36, 36};

            yellowPlayer.texture = textures[TGREY];
            yellowPlayer.mask = (Rectangle) {195, 0, 49, 49};
        }

        DrawText("N° de jugadores:     3           4", 20, 40, 20, BLACK);
        DrawTextureRec(threePlayers.texture, threePlayers.mask, threePlayers.position, WHITE);
        DrawTextureRec(fourPlayers.texture, fourPlayers.mask, fourPlayers.position, WHITE);

        DrawTexturePro(redPlayer.texture, redPlayer.mask, redPlayer.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(bluePlayer.texture, bluePlayer.mask, bluePlayer.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(greenPlayer.texture, greenPlayer.mask, greenPlayer.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(yellowPlayer.texture, yellowPlayer.mask, yellowPlayer.resize, (Vector2) {0, 0}, 0, WHITE);

        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {93, 250,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {403, 250,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {93, 480,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {403, 480,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawText(names[playerNames[REDNAME]], 110, 265, 20, BLACK);
        DrawText(names[playerNames[BLUENAME]], 420, 265, 20, BLACK);
        DrawText(names[playerNames[GREENNAME]], 110, 495, 20, BLACK);
        DrawText(names[playerNames[YELLOWNAME]], 420, 495, 20, BLACK);

        DrawTextureRec(changePlayer.texture, changePlayer.mask, (Vector2) {258, 196}, WHITE);
        DrawTextureRec(changePlayer.texture, changePlayer.mask, (Vector2) {568, 196}, WHITE);
        DrawTextureRec(changePlayer.texture, changePlayer.mask, (Vector2) {258, 426}, WHITE);
        DrawTextureRec(changePlayer.texture, changePlayer.mask, (Vector2) {568, 426}, WHITE);

        DrawTextureRec(ready.texture, ready.mask, ready.position, WHITE);
        DrawText("Comenzar", 270, 550, 30, BLACK);
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

        // Buttons functionality

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // N° of players buttons

            if (CheckCollisionPointRec(mousePoint, threePlayers.collision))
            {
                threePlayers.status = 1;
                fourPlayers.status = 0;
                playerCount = 3;
                playerNames[YELLOWNAME] = 6;
            }
            else if (CheckCollisionPointRec(mousePoint, fourPlayers.collision))
            {
                fourPlayers.status = 1;
                threePlayers.status = 0;
                playerCount = 4;
                playerNames[YELLOWNAME] = ChangeCharacter(playerNames, playerNames[YELLOWNAME]);
            }

            // Change character buttons

            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {258, 196, 36, 36}))
            {
                playerNames[REDNAME] = ChangeCharacter(playerNames, playerNames[REDNAME]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {568, 196, 36, 36}))
            {
                playerNames[BLUENAME] = ChangeCharacter(playerNames, playerNames[BLUENAME]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {258, 426, 36, 36}))
            {
                playerNames[GREENNAME] = ChangeCharacter(playerNames, playerNames[GREENNAME]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {568, 426, 36, 36}))
            {
                playerNames[YELLOWNAME] = ChangeCharacter(playerNames, playerNames[YELLOWNAME]);
            }

            // start button

            else if (CheckCollisionPointRec(mousePoint, ready.collision))
            {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {
                    ready.texture = textures[TYELLOW];
                    ready.mask = (Rectangle) {0, 50, 190, 45};
                    ready.status = 1;
                }
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePoint, ready.collision))
            {
                // Start the game
            }
            else
            {
                ready.texture = textures[TGREEN];
                ready.mask = (Rectangle) {0, 0,190, 49};
                ready.status = 0;
            }
        }

        // exit button

        if (CheckCollisionPointRec(mousePoint, exit.collision) && ready.status == 0)
        {
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
            exit.texture = textures[TGREY];
            exit.mask = (Rectangle) {186, 433, 36, 35};
        }

        EndDrawing();
    }
    SetWindowSize(600, 500);
}

int ChangeCharacter(int namesInUse[4], int actualName) {
    int newName = (actualName + 1) % 6;
    bool nameExists = false;

    for (int i = 0; i < 4; i++) {
        if (newName == namesInUse[i])
            nameExists = true;
    }

    if (nameExists) {
        newName = ChangeCharacter(namesInUse, newName);
    } else {
        return newName;
    }

    return newName;
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
            exit.texture = textures[TGREY];
            exit.mask = (Rectangle) {186, 433, 36, 35};
        }

        EndDrawing();
    }
    SetWindowTitle("Who killed Ms. Gladis?");
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
            exit.texture = textures[TGREY];
            exit.mask = (Rectangle) {186, 433, 36, 35};
        }

        EndDrawing();
    }
    SetWindowTitle("Who killed Ms. Gladis?");
}