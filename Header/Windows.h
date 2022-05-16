void MainWindow();
void AboutWindow(Texture2D textures[]);
void ChoosePlayers(Texture2D textures[]);
void HowtoPlayWindow(Texture2D textures[], Texture2D tutorialT);
int ChangeCharacter(int namesInUse[4], int actualName);

void MainWindow()
{
    InitWindow(600, 500, "Who killed Mrs. Gladis?");
    Vector2 mousePoint;

    Texture2D TRed = LoadTexture("../Assets/redSheet.png");
    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TGreen = LoadTexture("../Assets/greenSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");
    Texture2D guiTextures[] = {TRed, TBlue, TGreen, TYellow, TGrey};

    Texture2D tutorialT = LoadTexture("../Assets/Tutorial.png");

    Button start = {
            guiTextures[TBLUE],
            {225, 200},
            {0,94,190, 49},
            {start.position.x, start.position.y, start.mask.width, start.mask.height},
            0
    };
    Button how = {
            guiTextures[TBLUE],
            {225, 260},
            {0, 94,190, 49},
            {how.position.x, how.position.y, how.mask.width, how.mask.height},
            0
    };
    Button about = {
            guiTextures[TGREEN],
            {225, 330},
            {0, 0,190, 49},
            {about.position.x, about.position.y, about.mask.width, about.mask.height},
            0
    };
    Button exit = {
            guiTextures[TRED],
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

        DrawText("Who Killed Mrs. Gladis?", 10, 100, 50, BLACK);

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
                    start.texture = guiTextures[TYELLOW];
                    start.mask = (Rectangle) {0, 50, 190, 45};
                    start.status = 1;
                }
                else if (CheckCollisionPointRec(mousePoint, how.collision))
                {
                    how.texture = guiTextures[TYELLOW];
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
                    if (playerCount)
                    {
                        EndDrawing();
                        break;
                    }
                }
            }
            else if (CheckCollisionPointRec(mousePoint, how.collision))
            {
                if (how.status)
                {
                    EndDrawing();
                    HowtoPlayWindow(guiTextures, tutorialT);
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

            start.texture = guiTextures[TBLUE];
            start.mask = (Rectangle) {0,94,190, 49};
            start.status = 0;

            how.texture = guiTextures[TBLUE];
            how.mask = (Rectangle) {0, 94, 190, 49};
            how.status = 0;

            about.texture = guiTextures[TGREEN];
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
    bool gameWillStart = false;
    Vector2 mousePoint;
    playerCount = 4;
    Texture2D circleArrows = LoadTexture("../Assets/changePlayer.png");
    Texture2D profilePics = LoadTexture("../Assets/charProfiles.png");

    Rectangle gladisMask = {0, 0, 64, 64};
    Rectangle kimMask = {profilePics.width / 6, 0, 64, 64};
    Rectangle hildaMask = {(profilePics.width * 2) / 6, 0, 64, 64};
    Rectangle colonelMask = {(profilePics.width * 3) / 6, 0, 64, 64};
    Rectangle boyMask = {(profilePics.width * 4) / 6, 0, 64, 64};
    Rectangle detectiveMask = {(profilePics.width * 5) / 6, 0, 64, 64};
    Rectangle profileMasks[] = {gladisMask, colonelMask, kimMask, boyMask, hildaMask, detectiveMask};

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
    Picture redPlayerFrame = {
        textures[TRED],
        {337, 188, 49, 49},
        {110, 95, redPlayerFrame.mask.width * 3, redPlayerFrame.mask.height * 3},
    };
    Picture bluePlayerFrame = {
        textures[TBLUE],
        {288, 194, 49, 49},
        {420, 95, bluePlayerFrame.mask.width * 3, bluePlayerFrame.mask.height * 3}
    };
    Picture greenPlayerFrame = {
        textures[TGREEN],
        {337, 184, 49, 49},
        {110, 325, greenPlayerFrame.mask.height * 3, greenPlayerFrame.mask.height * 3}
    };
    Picture yellowPlayerFrame = {
        textures[TYELLOW],
        {190, 194, 49, 49},
        {420, 325, yellowPlayerFrame.mask.width * 3, yellowPlayerFrame.mask.height * 3}
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

            yellowPlayerFrame.texture = textures[TYELLOW];
            yellowPlayerFrame.mask = (Rectangle) {190, 194, 49, 49};
        }
        else if (threePlayers.status) {
            threePlayers.texture = textures[TBLUE];
            threePlayers.mask = (Rectangle) {386, 210, 36, 36};
            fourPlayers.texture = textures[TGREY];
            fourPlayers.mask = (Rectangle) {185, 469, 36, 36};

            yellowPlayerFrame.texture = textures[TGREY];
            yellowPlayerFrame.mask = (Rectangle) {195, 0, 49, 49};
        }

        DrawText("N° de jugadores:     3           4", 20, 40, 20, BLACK);
        DrawTextureRec(threePlayers.texture, threePlayers.mask, threePlayers.position, WHITE);
        DrawTextureRec(fourPlayers.texture, fourPlayers.mask, fourPlayers.position, WHITE);

        DrawTexturePro(redPlayerFrame.texture, redPlayerFrame.mask, redPlayerFrame.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(bluePlayerFrame.texture, bluePlayerFrame.mask, bluePlayerFrame.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(greenPlayerFrame.texture, greenPlayerFrame.mask, greenPlayerFrame.resize, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(yellowPlayerFrame.texture, yellowPlayerFrame.mask, yellowPlayerFrame.resize, (Vector2) {0, 0}, 0, WHITE);

        DrawTexturePro(profilePics, profileMasks[playerId[REDPLAYER]], (Rectangle) {125, 110,117, 105}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[BLUEPLAYER]], (Rectangle) {435, 110,117, 105}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[GREENPLAYER]], (Rectangle) {125, 340,117, 105}, (Vector2) {0, 0}, 0, WHITE);
        if (playerCount == 4)
            DrawTexturePro(profilePics, profileMasks[playerId[YELLOWPLAYER]], (Rectangle) {435, 340,117, 105}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {93, 250,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {403, 250,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {93, 480,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(nameHolder.texture, nameHolder.mask, (Rectangle) {403, 480,  186, 40}, (Vector2) {0, 0}, 0, WHITE);
        DrawText(names[playerId[REDPLAYER]], 110, 265, 20, BLACK);
        DrawText(names[playerId[BLUEPLAYER]], 420, 265, 20, BLACK);
        DrawText(names[playerId[GREENPLAYER]], 110, 495, 20, BLACK);
        DrawText(names[playerId[YELLOWPLAYER]], 420, 495, 20, BLACK);

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
                playerId[YELLOWPLAYER] = 6;
            }
            else if (CheckCollisionPointRec(mousePoint, fourPlayers.collision))
            {
                fourPlayers.status = 1;
                threePlayers.status = 0;
                playerCount = 4;
                playerId[YELLOWPLAYER] = ChangeCharacter(playerId, playerId[YELLOWPLAYER]);
            }

            // Change character buttons

            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {258, 196, 36, 36}))
            {
                playerId[REDPLAYER] = ChangeCharacter(playerId, playerId[REDPLAYER]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {568, 196, 36, 36}))
            {
                playerId[BLUEPLAYER] = ChangeCharacter(playerId, playerId[BLUEPLAYER]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {258, 426, 36, 36}))
            {
                playerId[GREENPLAYER] = ChangeCharacter(playerId, playerId[GREENPLAYER]);
            }
            else if (CheckCollisionPointRec(mousePoint, (Rectangle) {568, 426, 36, 36}))
            {
                if (playerCount == 4)
                    playerId[YELLOWPLAYER] = ChangeCharacter(playerId, playerId[YELLOWPLAYER]);
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
                gameWillStart = true;
                EndDrawing();
                break;
            }
            ready.texture = textures[TGREEN];
            ready.mask = (Rectangle) {0, 0,190, 49};
            ready.status = 0;
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
    if (!gameWillStart)
        playerCount = 0;
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

void HowtoPlayWindow(Texture2D textures[], Texture2D tutorialT) {
    SetWindowTitle("Cómo Jugar");
    Vector2 mousePoint;
    Button exit = {
            textures[TGREY],
            {550, 450},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };
    int tutorialImageCount = 8;
    int tutorialShowing = 0;
    int NUMTOASCII = 49;
    char actualPage[2] = {tutorialShowing + NUMTOASCII, '\0'};
    Picture tutorialPics = {
            tutorialT,
            {(tutorialT.width * tutorialShowing) / tutorialImageCount, 0, tutorialT.width / tutorialImageCount, tutorialT.height},
            {75, 20, (tutorialT.width / tutorialImageCount) * 0.5, tutorialT.height * 0.5}
    };
    Picture switchArrowLeft = {
            textures[TBLUE],
            {339, 143, 39, 31},
            {10, 200, 39, 31}
    };
    Picture switchArrowRight = {
            textures[TBLUE],
            {378, 143, 39, 31},
            {555, 200, 39, 31}
    };

    while (!WindowShouldClose())
    {
        actualPage[0] = tutorialShowing + NUMTOASCII;
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTexturePro(tutorialPics.texture, (Rectangle) {(tutorialT.width * tutorialShowing) / tutorialImageCount, 0, tutorialT.width / tutorialImageCount, tutorialT.height}, tutorialPics.resize, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
        DrawTexturePro(switchArrowLeft.texture, switchArrowLeft.mask, switchArrowLeft.resize, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(switchArrowRight.texture, switchArrowRight.mask, switchArrowRight.resize , (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText(actualPage, 25, 450, 15, BLACK);
        DrawText("/8", 35, 450, 15, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePoint, switchArrowLeft.resize))
            {
                if (tutorialShowing > 0)
                    tutorialShowing--;
            }
            if (CheckCollisionPointRec(mousePoint, switchArrowRight.resize))
            {
                tutorialShowing = (tutorialShowing + 1) % tutorialImageCount;
            }
        }

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
    SetWindowTitle("Who killed Mrs. Gladis?");
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
    char aboutText[] =
            "Who Killed Mrs. Gladys\n\nCreado por:\n- Carolina Arellano\n- Luis Acosta\n\nLink a Github:";
    char gitLink[] = "https://github.com/LuisA-15/Who-killed-Ms.-Gladis-";
    Button linkBox = {
            .collision = {20, 250, 535, 20},
            .status = 0
    };
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground((Color) {189, 195, 199});
        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
        DrawText(aboutText, 20, 30, 20, BLACK);
        DrawText(gitLink, 20, 250, 20, DARKBLUE);

        if (CheckCollisionPointRec(mousePoint, linkBox.collision))
        {
            DrawRectangleLines(18, 270, 535, 1, DARKBLUE);
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                linkBox.status = 1;
            }
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePoint, linkBox.collision))
            {
                if (linkBox.status)
                    OpenURL(gitLink);
            }
        }
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
    SetWindowTitle("Who killed Mrs. Gladis?");
}