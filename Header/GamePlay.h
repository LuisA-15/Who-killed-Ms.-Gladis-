void Gameplay();
int ShuffleCards(int cardsInUse[18], int index);
void AssignCards(Player players[], int shuffledCards[]);
void ShowCards(Texture2D guiT[], Vector2 mouse, Texture2D sheet, Player players[], Texture2D cardsT);
void Options(Texture2D guiT[], Vector2 mouse);
void Movement(Player player[]);
void DrawNameOfPlace(Texture2D placeT, Rectangle placesMasks[], Player activeP);

void Gameplay() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Who killed Mrs. Gladys?");
    MaximizeWindow();
    Vector2 mousePoint;

    for (int i = 0; i < 2; i++)
        bgMusic[i] = LoadMusicStream(bgMusicPaths[i]);
    nowPlaying = GetRandomValue(0, 1);
    PlayMusicStream(bgMusic[nowPlaying]);

    Texture2D board = LoadTexture("../Assets/board/board.png");

    Texture2D TRed = LoadTexture("../Assets/redSheet.png");
    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TGreen = LoadTexture("../Assets/greenSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");
    Texture2D guiTextures[] = {TRed, TBlue, TGreen, TYellow, TGrey};

    Texture2D cards = LoadTexture("../Assets/Cards.png");
    Texture2D items = LoadTexture("../Assets/item icons.png");

    Rectangle notesMask = {items.width * 6 / 9, 0, 70, 70};
    Rectangle casefileMask = {items.width * 7 / 9, 0, 70, 70};
    Rectangle notesSelectedMask = {items.width * 8 / 9, 0, 70, 70};
    Rectangle itemsMasks[] = {notesMask, casefileMask, notesSelectedMask};

    Texture2D notesSheet = LoadTexture("../Assets/notesSheet.png");

    Texture2D placesNames = LoadTexture("../Assets/Places names.png");
    Rectangle pNamesMasks[] = {
            {0, 0, 59, 29},
            {59, 0, 72, 14},
            {131, 0, 87, 14},
            {218, 0, 72, 14},
            {290, 0, 77, 14},
            {367, 0, 70, 14}
    };

    Texture2D profilePics = LoadTexture("../Assets/charProfiles.png");
    Rectangle gladisMask = {0, 0, 64, 64};
    Rectangle kimMask = {profilePics.width / 6, 0, 64, 64};
    Rectangle hildaMask = {(profilePics.width * 2) / 6, 0, 64, 64};
    Rectangle colonelMask = {(profilePics.width * 3) / 6, 0, 64, 64};
    Rectangle boyMask = {(profilePics.width * 4) / 6, 0, 64, 64};
    Rectangle detectiveMask = {(profilePics.width * 5) / 6, 0, 64, 64};
    Rectangle profileMasks[] = {gladisMask, colonelMask, kimMask, boyMask, hildaMask, detectiveMask};

    Player players[] = {redPlayer, bluePlayer, greenPlayer, yellowPlayer};

    // Load board collisions and movement available
    CreateBoard();

    // Sort cards to each player and create a solution
    gameAnswer.suspect = GetRandomValue(MARYPOPPINS, MAX);
    gameAnswer.weapon = GetRandomValue(KNIFE, STEAK);
    gameAnswer.place = GetRandomValue(LIVING, GARAGE);

    int sortedCards[18] = {gameAnswer.suspect, gameAnswer.weapon, gameAnswer.place};
    for (int i = 2; i < 18; i++)
        sortedCards[i] = ShuffleCards(sortedCards, i);
    AssignCards(players, sortedCards);

    Button showCardsButton = {
        items,
        {216, 85 + (activePlayer * 160)},
        itemsMasks[NOTESSELECTED],
        {showCardsButton.position.x, showCardsButton.position.y, 70, 70},
        0
    };
    Button rollDice = {
            guiTextures[TBLUE],
            {1050, 350},
            {0,94,190, 49},
            {1050, 350, 380, 90},
            0
    };
    Button suspectButton = {
            guiTextures[TGREEN],
            {1050, 450},
            {0, 0,190, 49},
            {1050, 450, 380, 90},
            0
    };
    Button accuseButton = {
            guiTextures[TRED],
            {1050, 550},
            {190, 0, 190, 49},
            {1050, 550, 380, 90},
            0
    };
    Button optionsButton = {
            guiTextures[TGREY],
            {1200, 650},
            {0, 237, 190, 49},
            {1200, 650, 190, 49},
            0
    };

    while(!WindowShouldClose())
    {
        if (gameFlags[GAMESHOULDCLOSE])
        {
            EndDrawing();
            break;
        }
        SetMusicVolume(bgMusic[nowPlaying], musicVolume);
        UpdateMusicStream(bgMusic[nowPlaying]);
        BeginDrawing();
        ClearBackground(DARKBROWN);
        mousePoint = GetMousePosition();
        DrawTextureRec(board, (Rectangle) {0, 0, board.width, board.height}, (Vector2) {400, 10}, RAYWHITE);

        // Draw Characters
        DrawRectangle(35, 35, 300, 138, MAROON);
        DrawRectangle(35, 195, 300, 138, DARKBLUE);
        DrawRectangle(35, 355, 300, 138, DARKGREEN);
        DrawRectangle(35, 515, 300, 138, GOLD);
        DrawTexturePro(profilePics, profileMasks[playerId[REDPLAYER]], (Rectangle) {40, 40, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[BLUEPLAYER]], (Rectangle) {40, 200, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[GREENPLAYER]], (Rectangle) {40, 360, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[YELLOWPLAYER]], (Rectangle) {40, 520, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawRectangle(173, 40, 157, 30, GRAY);
        DrawRectangle(173, 200, 157, 30, GRAY);
        DrawRectangle(173, 360, 157, 30, GRAY);
        DrawRectangle(173, 520, 157, 30, GRAY);
        DrawText(names[playerId[REDPLAYER]], 178, 45, 20, BLACK);
        DrawText(names[playerId[BLUEPLAYER]], 178, 205, 20, BLACK);
        DrawText(names[playerId[GREENPLAYER]], 178, 365, 20, BLACK);
        DrawText(names[playerId[YELLOWPLAYER]], 178, 525, 20, BLACK);

        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 85}, RAYWHITE);
        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 245}, RAYWHITE);
        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 405}, RAYWHITE);
        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 565}, RAYWHITE);

        // Change show cards button depending on active player
        showCardsButton.position.y = 85 + (activePlayer * 160);
        showCardsButton.collision.y = showCardsButton.position.y;

        if (showCardsButton.status)
            DrawTextureRec(items, itemsMasks[NOTESSELECTED], (Vector2) {216, showCardsButton.position.y}, RAYWHITE);

        // Active Player marker
        DrawRectangle(10, 35 + (160 * activePlayer), 20, 138, YELLOW);

        // Draw Action buttons
        DrawTexturePro(rollDice.texture, rollDice.mask, rollDice.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(suspectButton.texture, suspectButton.mask, suspectButton.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(accuseButton.texture, accuseButton.mask, accuseButton.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(optionsButton.texture, optionsButton.mask, optionsButton.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("Tirar dado", 1080, 365, 50, BLACK);
        DrawText("Sospechar", 1080, 465, 50, BLACK);
        DrawText("Acusar", 1130, 565, 50, BLACK);
        DrawText("Opciones", 1220, 660, 30, BLACK);

        // Draw Name of nearby place
        DrawNameOfPlace(placesNames, pNamesMasks, players[activePlayer]);

        // Button functions
        if (gameFlags[SHOWCARDS])
        {
            ShowCards(guiTextures, mousePoint, notesSheet, players, cards);
        }
        else if (gameFlags[OPTIONS])
        {
            Options(guiTextures, mousePoint);
        }
        else
        {
            Movement(players);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(mousePoint, showCardsButton.collision)) {
                        showCardsButton.status = 1;
                    }
                    else if (CheckCollisionPointRec(mousePoint, optionsButton.collision))
                    {
                        optionsButton.status = 1;
                    }
                }
            }
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePoint, showCardsButton.collision))
                {
                    if (showCardsButton.status)
                        gameFlags[SHOWCARDS] = true;
                }
                else if (CheckCollisionPointRec(mousePoint, optionsButton.collision))
                {
                    if (optionsButton.status)
                        gameFlags[OPTIONS] = true;
                }
                showCardsButton.status = 0;
                optionsButton.status = 0;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    if (gameFlags[GAMESHOULDRESTART])
    {
        RestartValues(playerCount);
        Gameplay();
    }
}

int ShuffleCards(int cardsInUse[], int index)
{
    int randomCard = GetRandomValue(MARYPOPPINS, GARAGE);
    for (int i = index; i >= 0; i--)
    {
        if (randomCard == cardsInUse[i])
        {
            return ShuffleCards(cardsInUse, index);
        }
    }
    return randomCard;
}

void AssignCards(Player players[], int shuffledCards[])
{
    int cardsForEachPlayer = 5;
    if (playerCount == 4)
        cardsForEachPlayer = 3;

    for (int player = REDPLAYER; player <= YELLOWPLAYER; player++)
    {
        // Assign to each player a part of the shuffled cards
        for (int i = 0; i < cardsForEachPlayer; i++)
            players[player].cards[i] = shuffledCards[3 * (player + 1) + i];
        players[player].cards[5] = NULLCARD;
    }

    if (playerCount == 4) {
        int unusedCards[3] = {shuffledCards[15], shuffledCards[16], shuffledCards[17]};
        for (int player = REDPLAYER; player <= YELLOWPLAYER; player++)
        {
            players[player].cards[3] = unusedCards[0];
            players[player].cards[4] = unusedCards[1];
            players[player].cards[5] = unusedCards[2];
        }
    }
}

void ShowCards(Texture2D guiT[], Vector2 mouse, Texture2D sheet, Player players[], Texture2D cardsT)
{
    Picture notesSheet = {
            sheet,
            {0, 0, sheet.width, sheet.height},
            {875, 10, sheet.width, GetScreenHeight() - 21}
    };
    Picture cross = {
            guiT[TGREY],
            {120, 478, 18, 18}
    };
    Button exit = {
            guiT[TGREY],
            {GetScreenWidth() - 50, GetScreenHeight() - 50},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };

    // Background transparent black screen
    DrawRectangle(0, 0, GetScreenWidth(),  GetScreenHeight(), (Color) {0, 0, 0, 125});

    DrawTexturePro(notesSheet.texture, notesSheet.mask, notesSheet.resize, (Vector2) {0, 0}, 0, RAYWHITE);

    // Click to checkmark sheet function
    for (int i = 0; i < GARAGE; i++)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, (Rectangle) {1233, 99 + (33 * i), 68, 33}))
            {
                if (playersNotes[activePlayer][i])
                {
                    playersNotes[activePlayer][i] = false;
                }
                else
                {
                    playersNotes[activePlayer][i] = true;
                }
            }
        }
        if (playersNotes[activePlayer][i])
        {
            DrawTextureRec(cross.texture, cross.mask, (Vector2) {1258, 105 + (33 * i)}, RAYWHITE);
        }
    }

    // Show player's cards
    for (int i = 0; i < 3; i++)
    {
        Rectangle cardsResizeLeft = {
                256,
                25 + (210 * i),
                150,
                192
        };
        Rectangle cardsResizeRight = {
                450,
                25 + (210 * i),
                150,
                192
        };
        DrawTexturePro(cardsT, (Rectangle) {100 * (players[activePlayer].cards[i] - 1), 0, 100, 128}, cardsResizeLeft, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(cardsT, (Rectangle) {100 * (players[activePlayer].cards[i + 3] - 1), 0, 100, 128}, cardsResizeRight, (Vector2) {0, 0}, 0, RAYWHITE);
    }

    // Exit button
    if (CheckCollisionPointRec(mouse, exit.collision))
    {
        exit.texture = guiT[TRED];
        exit.mask = (Rectangle) {381, 36, 36, 36};
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, exit.collision))
        {
            gameFlags[SHOWCARDS] = false;
        }
    }
    DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
}

void Options(Texture2D guiT[], Vector2 mouse)
{
    Picture window = {
            guiT[TGREY],
            {190, 98, 100, 100},
            {285, 50, 800, 600}
    };
    Picture musicSlider = {
            guiT[TGREY],
            {227, 203, 115, 19},
            {675, 170, 345, 57}
    };
    Picture sliderMark = {
            guiT[TGREY],
            {190, 234, 28, 41},
            {675 + (musicVolume * 295), 155, 42, 62}
    };
    Button volumeDown = {
            guiT[TGREY],
            {665, 235},
            {0, 478, 39, 31},
            {665, 235, 39, 31},
    };
    Button volumeUp = {
            guiT[TGREY],
            {985, 235},
            {39, 478, 39, 31},
            {985, 235, 39, 31},
    };
    Button changeMusic = {
            guiT[TGREY],
            {385, 280},
            {0, 98, 190, 45},
            {changeMusic.position.x, changeMusic.position.y, changeMusic.mask.width * 1.25, changeMusic.mask.height * 1.25}
    };
    Picture musicNameHolder = {
            guiT[TGREY],
            {2, 52, 186, 45},
            {650, 280, musicNameHolder.mask.width * 2, musicNameHolder.mask.height * 1.25}
    };
    Button restartGame = {
            guiT[TBLUE],
            {565, 460},
            {0, 94,190, 49},
            {restartGame.position.x, restartGame.position.y, restartGame.mask.width * 1.25, restartGame.mask.height * 1.25},
    };
    Button exitGame = {
            guiT[TRED],
            {565, 550},
            {190, 0, 190, 49},
            {exitGame.position.x, exitGame.position.y, exitGame.mask.width * 1.25, exitGame.mask.height * 1.25},
    };
    Button exit = {
            guiT[TGREY],
            {GetScreenWidth() - 50, GetScreenHeight() - 50},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
    };

    // Background transparent black screen
    DrawRectangle(0, 0, GetScreenWidth(),  GetScreenHeight(), (Color) {0, 0, 0, 125});

    DrawTexturePro(window.texture, window.mask, window.resize, (Vector2) {0, 0}, 0, RAYWHITE);

    if (gameFlags[OPENCONFIRMEXIT])
    {
        DrawTexturePro(guiT[TGREEN], (Rectangle) {381, 0, 36, 36}, (Rectangle) {550, 350, 72, 72}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(guiT[TRED], (Rectangle) {381, 36, 36, 36}, (Rectangle) {750, 350, 72, 72}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("¿Estás seguro?", 475, 200, 50, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Confirm exit
            if (CheckCollisionPointRec(mouse, (Rectangle) {550, 350, 72, 72}))
            {
                gameFlags[GAMESHOULDCLOSE] = true;
            }
            // Cancel exit
            else if (CheckCollisionPointRec(mouse, (Rectangle) {750, 350, 72, 72}))
            {
                gameFlags[OPENCONFIRMEXIT] = false;
                gameFlags[GAMESHOULDRESTART] = false;
            }
        }
    }
    else
    {
        // Change volume buttons function
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, volumeUp.collision))
            {
                if (musicVolume < 1.0)
                    musicVolume += 0.2;
            }
            else if (CheckCollisionPointRec(mouse, volumeDown.collision))
            {
                if(musicVolume > 0.2)
                    musicVolume -= 0.2;
            }
        }

        // Change music button
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, changeMusic.collision))
            {
                PauseMusicStream(bgMusic[nowPlaying]);
                nowPlaying = (nowPlaying + 1) % 2;
                if (!IsMusicStreamPlaying(bgMusic[nowPlaying]))
                    PlayMusicStream(bgMusic[nowPlaying]);
                ResumeMusicStream(bgMusic[nowPlaying]);
            }
        }

        // Restart game button
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, restartGame.collision))
            {
                gameFlags[OPENCONFIRMEXIT] = true;
                gameFlags[GAMESHOULDRESTART] = true;
            }
        }

        // Exit game button
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, exitGame.collision))
                gameFlags[OPENCONFIRMEXIT] = true;
        }

        // Exit button
        if (CheckCollisionPointRec(mouse, exit.collision))
        {
            exit.texture = guiT[TRED];
            exit.mask = (Rectangle) {381, 36, 36, 36};
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, exit.collision))
            {
                gameFlags[OPTIONS] = false;
            }
        }

        DrawText("Opciones", 550, 85, 55, BLACK);

        DrawText("Volumen de la música", 330, 170, 30, BLACK);
        DrawTexturePro(volumeDown.texture, volumeDown.mask, volumeDown.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(volumeUp.texture, volumeUp.mask, volumeUp.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(musicSlider.texture, musicSlider.mask, musicSlider.resize, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(sliderMark.texture, sliderMark.mask, sliderMark.resize, (Vector2) {0, 0}, 0, RAYWHITE);

        DrawTexturePro(changeMusic.texture, changeMusic.mask, changeMusic.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("Cambiar música", 413, 297, 25, BLACK);
        DrawTexturePro(musicNameHolder.texture, musicNameHolder.mask, musicNameHolder.resize, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText(bgMusicNames[nowPlaying], 660, 300, 25, BLACK);

        DrawTexturePro(restartGame.texture, restartGame.mask, restartGame.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("Reiniciar juego", 587, 475, 27, BLACK);
        DrawTexturePro(exitGame.texture, exitGame.mask, exitGame.collision, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("Salir del Juego", 587, 565, 27, BLACK);

        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
    }
}

void Movement(Player player[])
{
    switch (GetKeyPressed()) {
        case KEY_W:
        case KEY_UP:
            if(boardGrid[player[activePlayer].row - 1][player[activePlayer].column] == SHORTCUT)
            {
                player[activePlayer].row -= 15;
            }
            else if(boardGrid[player[activePlayer].row - 1][player[activePlayer].column] != UNABLE)
            {
                player[activePlayer].row -= 1;
            } break;

        case KEY_A:
        case KEY_LEFT:
            if(boardGrid[player[activePlayer].row][player[activePlayer].column - 1] == SHORTCUT)
            {
                player[activePlayer].column -= 5;
            }
            else if(boardGrid[player[activePlayer].row][player[activePlayer].column - 1] != UNABLE) {
                player[activePlayer].column -= 1;
            } break;

        case KEY_S:
        case KEY_DOWN:
            if(boardGrid[player[activePlayer].row + 1][player[activePlayer].column] == SHORTCUT)
            {
                player[activePlayer].row += 15;
            }
            else if(boardGrid[player[activePlayer].row + 1][player[activePlayer].column] != UNABLE)
            {
                player[activePlayer].row += 1;
            } break;

        case KEY_D:
        case KEY_RIGHT:
            if(boardGrid[player[activePlayer].row][player[activePlayer].column + 1] == SHORTCUT)
            {
                player[activePlayer].column += 5;
            }
            else if(boardGrid[player[activePlayer].row][player[activePlayer].column + 1] != UNABLE)
            {
                player[activePlayer].column += 1;
            } break;
    }
}

void DrawNameOfPlace(Texture2D placeT, Rectangle placesMasks[], Player activeP)
{
    if (activeP.column <= 3)
    {
        if (activeP.row >= 13 && activeP.row <= 17)
            DrawTexturePro(placeT, placesMasks[0],
                           (Rectangle) {520, 450, placesMasks[0].width, placesMasks[0].height},
                           (Vector2) {0, 0}, -90, RAYWHITE);
        else if (activeP.row >= 5 && activeP.row <= 9)
            DrawTexturePro(placeT, placesMasks[1],
                           (Rectangle) {530, 310, placesMasks[1].width, placesMasks[1].height},
                           (Vector2) {0, 0}, -90, RAYWHITE);
    }
    else if (activeP.column >= 3 && activeP.column <= 7)
    {
        if (activeP.row <= 3)
            DrawTexturePro(placeT, placesMasks[2],
                           (Rectangle) {580, 140, placesMasks[2].width, placesMasks[2].height},
                           (Vector2) {0, 0}, 0, RAYWHITE);
    }
    else if (activeP.column >= 10)
    {
        if (activeP.row >= 8 && activeP.row <= 12)
            DrawTexturePro(placeT, placesMasks[3],
                           (Rectangle) {780, 259, placesMasks[3].width, placesMasks[3].height},
                           (Vector2) {0, 0}, 90, RAYWHITE);
        else if (activeP.row >= 15 && activeP.row <= 19)
            DrawTexturePro(placeT, placesMasks[4],
                           (Rectangle) {780, 420, placesMasks[4].width, placesMasks[4].height},
                           (Vector2) {0, 0}, 90, RAYWHITE);
    }
    if (activeP.column >= 5 && activeP.column <= 9)
    {
        if (activeP.row >= 18)
            DrawTexturePro(placeT, placesMasks[5],
                           (Rectangle) {700, 540, placesMasks[5].width, placesMasks[5].height},
                           (Vector2) {0, 0}, 180, RAYWHITE);
    }
}