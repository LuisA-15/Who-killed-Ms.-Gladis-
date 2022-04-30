void Gameplay();
int SortCards(int cardsInUse[18], int index);
void AssignCards(Player players[], int sortedCards[]);
void ShowCards(Texture2D guiT[], bool shouldShow[4], Vector2 mouse, Texture2D sheet, Player players[], Texture2D items, Rectangle cardsMask[]);
void Options(Texture2D guiT[], bool shouldShow[4], Vector2 mouse);

void Gameplay() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Who killed Mrs. Gladys?");
    MaximizeWindow();
    Vector2 mousePoint;

    Music backgroundMusic = LoadMusicStream("../Assets/Sounds/Persona 3 OST  When the Moons Reaching Out Stars.mp3");
    SetMusicVolume(backgroundMusic, musicVolume);
    PlayMusicStream(backgroundMusic);

    Texture2D board = LoadTexture("../Assets/board/board.png");

    Texture2D TRed = LoadTexture("../Assets/redSheet.png");
    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TGreen = LoadTexture("../Assets/greenSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");
    Texture2D guiTextures[] = {TRed, TBlue, TGreen, TYellow, TGrey};

    Texture2D items = LoadTexture("../Assets/item icons.png");
    Rectangle knifeMask = {0, 0, 70, 70};
    Rectangle gunMask = {items.width / 9, 0, 70, 70};
    Rectangle poisonMask = {items.width * 2 / 9, 0, 70, 70};
    Rectangle pantiesMask = {items.width * 3 / 9, 0, 70, 70};
    Rectangle jarMask = {items.width * 4 / 9, 0, 70, 70};
    Rectangle steakMask = {items.width * 5 / 9, 0, 70, 70};
    Rectangle cardMasks[] = {knifeMask, gunMask, poisonMask, pantiesMask, jarMask, steakMask};

    Rectangle notesMask = {items.width * 6 / 9, 0, 70, 70};
    Rectangle casefileMask = {items.width * 7 / 9, 0, 70, 70};
    Rectangle notesSelectedMask = {items.width * 8 / 9, 0, 70, 70};
    Rectangle itemsMasks[] = {notesMask, casefileMask, notesSelectedMask};

    Texture2D notesSheet = LoadTexture("../Assets/notesSheet.png");

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
        sortedCards[i] = SortCards(sortedCards, i);
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

    // Flags to show windows above board.
    bool shouldShowWindow[4] = {};

    while(!WindowShouldClose())
    {
        SetMusicVolume(backgroundMusic, musicVolume);
        UpdateMusicStream(backgroundMusic);
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

        // Button functions
        if (shouldShowWindow[SHOWCARDS])
        {
            ShowCards(guiTextures, shouldShowWindow, mousePoint, notesSheet, players, items, cardMasks);
        }
        else if (shouldShowWindow[OPTIONS])
        {
            Options(guiTextures, shouldShowWindow, mousePoint);
        }
        else
        {
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
                        shouldShowWindow[SHOWCARDS] = true;
                }
                else if (CheckCollisionPointRec(mousePoint, optionsButton.collision))
                {
                    if (optionsButton.status)
                        shouldShowWindow[OPTIONS] = true;
                }
                showCardsButton.status = 0;
                optionsButton.status = 0;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}

int SortCards(int cardsInUse[], int index)
{
    int randomCard = GetRandomValue(MARYPOPPINS, GARAGE);
    for (int i = index; i >= 0; i--)
    {
        if (randomCard == cardsInUse[i])
        {
            return SortCards(cardsInUse, index);
        }
    }
    return randomCard;
}

void AssignCards(Player players[], int sortedCards[])
{
    int cardsForEachPlayer = 5;
    if (playerCount == 4)
        cardsForEachPlayer = 3;

    for (int player = REDPLAYER; player <= YELLOWPLAYER; player++)
    {
        // Assign to each player a part of the sorted sortedCards
        for (int i = 0; i < cardsForEachPlayer; i++)
            players[player].cards[i] = sortedCards[3 * (player + 1) + i];
        players[player].cards[5] = NULLCARD;
    }

    if (playerCount == 4) {
        int unusedCards[3] = {sortedCards[15], sortedCards[16], sortedCards[17]};
        for (int player = REDPLAYER; player <= YELLOWPLAYER; player++)
        {
            players[player].cards[3] = unusedCards[0];
            players[player].cards[4] = unusedCards[1];
            players[player].cards[5] = unusedCards[2];
        }
    }
}

void ShowCards(Texture2D guiT[], bool shouldShow[4], Vector2 mouse, Texture2D sheet, Player players[], Texture2D items, Rectangle cardsMask[])
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
        DrawTextureRec(items, cardsMask[players[activePlayer].cards[i]], (Vector2) {200, 100 + 100 * i}, RAYWHITE);
        DrawTextureRec(items, cardsMask[players[activePlayer].cards[i + 3]], (Vector2) {400, 100 * i}, RAYWHITE);
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
            shouldShow[SHOWCARDS] = false;
        }
    }
    DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
}

void Options(Texture2D guiT[], bool shouldShow[4], Vector2 mouse)
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
            {675 + (musicVolume * 295), 135, 56, 82}
    };
    Button volumeDown = {
            guiT[TGREY],
            {665, 235},
            {0, 478, 39, 31},
            {665, 235, 39, 31},
            0
    };
    Button volumeUp = {
            guiT[TGREY],
            {985, 235},
            {39, 478, 39, 31},
            {985, 235, 39, 31},
            0
    };
    Button exitGame = {
            guiT[TRED],
            {700, 700},
            {190, 0, 190, 49},
            {exitGame.position.x, exitGame.position.y, exitGame.mask.width, exitGame.mask.height},
            0
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

    DrawTexturePro(window.texture, window.mask, window.resize, (Vector2) {0, 0}, 0, RAYWHITE);

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
            shouldShow[OPTIONS] = false;
        }
    }

    DrawText("Opciones", 550, 85, 55, BLACK);

    DrawText("Volumen de la música", 330, 170, 30, BLACK);
    DrawTexturePro(volumeDown.texture, volumeDown.mask, volumeDown.collision, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawTexturePro(volumeUp.texture, volumeUp.mask, volumeUp.collision, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawTexturePro(musicSlider.texture, musicSlider.mask, musicSlider.resize, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawTexturePro(sliderMark.texture, sliderMark.mask, sliderMark.resize, (Vector2) {0, 0}, 0, RAYWHITE);

    DrawTextureRec(exitGame.texture, exitGame.mask, (Vector2) {865, 575}, RAYWHITE);
    DrawText("Salir del Juego", 880, 590, 20, BLACK);

    DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

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
}