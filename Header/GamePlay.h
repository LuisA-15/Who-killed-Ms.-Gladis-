void Gameplay();
int  ShuffleCards(int cardsInUse[18], int index);
void AssignCards(Player players[], int shuffledCards[]);
void ShowCards(Texture2D guiT[], Vector2 mouse, Texture2D sheet, Player players[], Texture2D cardsT);
void Options(Texture2D guiT[], Vector2 mouse);
void Movement(Player player[]);
void UpdateRolledNumber(Player players[]);
void DrawNameOfPlace(Texture2D placeT, Rectangle placesMasks[], Player activeP);
void ShowAccusationInterface(Texture2D guiT[], Vector2 mouse, Texture2D sheet, Player players[], Texture2D cards);
void ChangeTurn(Player players[]);
bool IsSuspitionPossible(Player activeP);
bool StrongAccusation();
void StrongAccusationInterface(Texture2D guiT[], Vector2 mouse, Player players[], Texture2D profile, Rectangle masks[]);
void AdvertiseSuspect(Texture2D guiT[], Vector2 mouse, Texture2D cards, Player players[], Texture2D profiles, Rectangle profilesMasks[]);
int FindPlayerWithSuspects(Player players[]);
void RevealCardInterface(Player players[], Texture2D guiT[], Texture2D cards, Vector2 mouse);
void RevealCard(int card);
int GetPlayerPlace(Player player);
Color GetPlayerColor(int player);

void Gameplay() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Who killed Mrs. Gladys?");
    MaximizeWindow();
    float time = 0;
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
    Texture2D diceT = LoadTexture("../Assets/dice.png");
    Texture2D rollingDiceT = LoadTexture("../Assets/rollingDice.png");
    rollingDice.sprite.texture = rollingDiceT;
    Picture dice = {
            diceT,
            {0, 0, diceT.width / 6, diceT.height},
            {1100, 45, diceT.width / 12, diceT.height / 2}
    };

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
    players[activePlayer].movementLog[0][0] = players[activePlayer].column;
    players[activePlayer].movementLog[0][1] = players[activePlayer].row;
    players[activePlayer].movementLog[1][0] = players[activePlayer].column;
    players[activePlayer].movementLog[1][1] = players[activePlayer].row;

    // Load board collisions and movement available
    CreateBoard();

    // Sort cards to each player and create a solution
    gameAnswer.suspect = GetRandomValue(MARYPOPPINS, MAX);
    gameAnswer.weapon = GetRandomValue(KNIFE, STEAK);
    gameAnswer.place = GetRandomValue(LIVING, GARAGE);

    int sortedCards[18] = {gameAnswer.suspect, gameAnswer.weapon, gameAnswer.place};
    for (int i = 3; i < 18; i++)
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
            guiTextures[TGREY],
            {1050, 450},
            {0, 98, 190, 45},
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

    Button changeTurnButton = {
            guiTextures[TBLUE],
            {0, 0},
            {0,94,190, 49},
            {585, 615, 145, 35},
            0
    };

    Texture2D PlayerPiece = LoadTexture("../Assets/PLAYERS.png");

    redPlayer.piece.texture = PlayerPiece;
    bluePlayer.piece.texture = PlayerPiece;
    greenPlayer.piece.texture = PlayerPiece;
    yellowPlayer.piece.texture = PlayerPiece;

    // Testing function, prints game solution
    printf("%d, %d, %d", gameAnswer.place, gameAnswer.suspect, gameAnswer.weapon);

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
        if (playerCount == 4)
            DrawRectangle(35, 515, 300, 138, GOLD);
        for (int i = REDPLAYER; i <= YELLOWPLAYER; i++)
        {
            if (!players[i].inGame)
            {
                if (i == YELLOWPLAYER && playerCount == 3)
                    break;
                DrawRectangle(35, 35 + (160 * i), 300, 138, GRAY);
            }
        }
        DrawTexturePro(profilePics, profileMasks[playerId[REDPLAYER]], (Rectangle) {40, 40, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[BLUEPLAYER]], (Rectangle) {40, 200, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawTexturePro(profilePics, profileMasks[playerId[GREENPLAYER]], (Rectangle) {40, 360, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
        DrawRectangle(173, 40, 157, 30, GRAY);
        DrawRectangle(173, 200, 157, 30, GRAY);
        DrawRectangle(173, 360, 157, 30, GRAY);
        DrawText(names[playerId[REDPLAYER]], 178, 45, 20, BLACK);
        DrawText(names[playerId[BLUEPLAYER]], 178, 205, 20, BLACK);
        DrawText(names[playerId[GREENPLAYER]], 178, 365, 20, BLACK);
        if (playerCount == 4)
        {
            DrawTexturePro(profilePics, profileMasks[playerId[YELLOWPLAYER]], (Rectangle) {40, 520, 128, 128}, (Vector2) {0, 0}, 0, WHITE);
            DrawRectangle(173, 520, 157, 30, GRAY);
            DrawText(names[playerId[YELLOWPLAYER]], 178, 525, 20, BLACK);
            DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 565}, RAYWHITE);
        }

        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 85}, RAYWHITE);
        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 245}, RAYWHITE);
        DrawTextureRec(items, itemsMasks[NOTES], (Vector2) {216, 405}, RAYWHITE);

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
        DrawTexturePro(changeTurnButton.texture, changeTurnButton.mask, changeTurnButton.collision, (Vector2) {0, 0}, 0, RAYWHITE);

        DrawText("Tirar dado", 1080, 365, 50, BLACK);
        DrawText("Sospechar", 1080, 465, 50, BLACK);
        DrawText("Acusar", 1130, 565, 50, BLACK);
        DrawText("Opciones", 1220, 660, 30, BLACK);
        DrawText("Pasar Turno", 610, 625, 15, BLACK);

        // Draw Name of nearby place
        DrawNameOfPlace(placesNames, pNamesMasks, players[activePlayer]);

        bool enableSuspition = IsSuspitionPossible(players[activePlayer]);

        // Enable/Disable buttons
        if (gameFlags[DICEWASROLLED])
        {
            rollDice.texture = guiTextures[TGREY];
            rollDice.mask = (Rectangle) {0, 98, 190, 45};
        }
        if (enableSuspition && !gameFlags[SUSPECTHAPPENED])
        {
            suspectButton.texture = guiTextures[TGREEN];
            suspectButton.mask = (Rectangle) {0, 0,190, 49};
            if (suspectButton.status)
                suspectButton.mask = (Rectangle) {0, 192, 190, 45};
        }
        else
        {
            suspectButton.texture = guiTextures[TGREY];
            suspectButton.mask = (Rectangle) {0, 98, 190, 45};
        }

        DrawTexturePro(PlayerPiece, players[activePlayer].piece.mask, players[activePlayer].piece.resize, (Vector2){0,0}, 0, RAYWHITE);

        if (roll > 0)
        {
            dice.mask.x = (dice.texture.width / 6) * (roll - 1);
            DrawTexturePro(dice.texture, dice.mask, dice.resize, (Vector2) {0, 0}, 0, RAYWHITE);
        }

        // Button functions
        if (gameFlags[SHOWCARDS])
        {
            ShowCards(guiTextures, mousePoint, notesSheet, players, cards);
        }
        else if(gameFlags[PIECEISMOVING])
        {
            UpdatePosition(players);
        }
        else if (gameFlags[DICEISROLLING])
        {
            RollDice(time);
            time += GetFrameTime();
        }
        else if (gameFlags[OPTIONS])
        {
            Options(guiTextures, mousePoint);
        }
        else if (gameFlags[SUSPECT])
        {
            ShowAccusationInterface(guiTextures, mousePoint, notesSheet, players, cards);
        }
        else if(gameFlags[ACCUSATIONHAPPENING])
        {
            StrongAccusationInterface(guiTextures, mousePoint, players, profilePics, profileMasks);
        }
        else if (gameFlags[ADVERTISINGSUSPECT])
        {
            AdvertiseSuspect(guiTextures, mousePoint, cards, players, profilePics, profileMasks);
        }
        else if (gameFlags[REVEALCARD])
        {
            RevealCardInterface(players, guiTextures, cards, mousePoint);
        }
        else
        {
            if(roll > 0)
            {
                Movement(players);
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    if (CheckCollisionPointRec(mousePoint, showCardsButton.collision))
                    {
                        showCardsButton.status = 1;
                    }
                    else if (CheckCollisionPointRec(mousePoint, rollDice.collision))
                    {
                        if (!gameFlags[DICEWASROLLED])
                        {
                            rollDice.status = 1;
                            rollDice.mask = (Rectangle) {0, 49, 190, 45};
                        }
                    }
                    else if(CheckCollisionPointRec(mousePoint, suspectButton.collision))
                    {
                        suspectButton.status = 1;
                    }
                    else if(CheckCollisionPointRec(mousePoint, accuseButton.collision))
                    {
                        accuseButton.status =  1;
                        accuseButton.mask = (Rectangle) {0, 0, 190, 45};
                    }
                    else if (CheckCollisionPointRec(mousePoint, optionsButton.collision))
                    {
                        optionsButton.status = 1;
                    }
                    else if (CheckCollisionPointRec(mousePoint, changeTurnButton.collision))
                    {
                        changeTurnButton.mask = (Rectangle) {0, 49, 190, 45};
                        changeTurnButton.status = 1;
                    }
                }
            }
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePoint, showCardsButton.collision))
                {
                    if (showCardsButton.status)
                        gameFlags[SHOWCARDS] = true;
                }
                else if (CheckCollisionPointRec(mousePoint, rollDice.collision))
                {
                    if (rollDice.status)
                    {
                        gameFlags[DICEISROLLING] = true;
                        time = 0;
                    }
                }
                else if (CheckCollisionPointRec(mousePoint, suspectButton.collision))
                {
                    if (suspectButton.status)
                    {
                        if (enableSuspition && !gameFlags[SUSPECTHAPPENED])
                            gameFlags[SUSPECT] = true;
                    }
                }
                else if(CheckCollisionPointRec(mousePoint, accuseButton.collision))
                {
                    if(accuseButton.status)
                    {
                        if(enableSuspition)
                        {
                            gameFlags[SUSPECT] = true;
                            gameFlags[GOINGTOHAPPEN] = true;
                        }
                    }
                }
                else if (CheckCollisionPointRec(mousePoint, optionsButton.collision))
                {
                    if (optionsButton.status)
                        gameFlags[OPTIONS] = true;
                }
                else if (CheckCollisionPointRec(mousePoint, changeTurnButton.collision))
                {
                    if (changeTurnButton.status)
                    {
                        ChangeTurn(players);
                    }
                }

                showCardsButton.status = 0;
                rollDice.status = 0;
                optionsButton.status = 0;
                suspectButton.status = 0;
                suspectButton.mask = (Rectangle) {0, 0, 190, 49};
                changeTurnButton.status = 0;
                changeTurnButton.mask = (Rectangle) {0,94,190, 49};
                accuseButton.status = 0;
                accuseButton.mask = (Rectangle) {190, 0, 190, 49};

                if (!gameFlags[DICEWASROLLED])
                {
                    rollDice.texture = guiTextures[TBLUE];
                    rollDice.mask = (Rectangle) {0,94,190, 49};
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    if (gameFlags[GAMESHOULDRESTART])
    {
        RestartValues(players);
        Gameplay();
    }
}

int ShuffleCards(int cardsInUse[], int index)
{
    /*
     * Pull and return a random card that's not already been pulled
     */

    int randomCard = GetRandomValue(MARYPOPPINS, GARAGE);
    for (int k = index; k >= 0; k--)
    {
        if (randomCard == cardsInUse[k])
        {
            k = index;
            randomCard = GetRandomValue(MARYPOPPINS, GARAGE);
        }
    }
    return randomCard;
}

void AssignCards(Player players[], int shuffledCards[])
{
    if (playerCount == 3)
    {
        for (int i = REDPLAYER; i <= GREENPLAYER; i++)
        {
            for (int k = 0; k < 5; k++)
            {
                players[i].cards[k] = shuffledCards[3 + (5 * i) + k];
            }
            players[i].cards[5] = NULLCARD;
        }
    }
    else
    {
        for (int i = REDPLAYER; i <= YELLOWPLAYER; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                players[i].cards[k] = shuffledCards[3 + (3 * i) + k];
            }
            players[i].cards[3] = shuffledCards[15];
            players[i].cards[4] = shuffledCards[16];
            players[i].cards[5] = shuffledCards[17];
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
    positionUpdatedX = player[activePlayer].piece.resize.x;
    positionUpdatedY = player[activePlayer].piece.resize.y;
    switch (GetKeyPressed()) {
        case KEY_W:
        case KEY_UP:
            gameFlags[PIECEISMOVING] = true;
            if(boardGrid[player[activePlayer].row - 1][player[activePlayer].column] == SHORTCUT)
            {
                player[activePlayer].row -= 13;
                positionUpdatedY -= (13*18);
                UpdateRolledNumber(player);
            }
            else if(boardGrid[player[activePlayer].row - 1][player[activePlayer].column] != UNABLE)
            {
                player[activePlayer].row -= 1;
                positionUpdatedY -=  18;
                UpdateRolledNumber(player);
            }
            break;

        case KEY_A:
        case KEY_LEFT:
            gameFlags[PIECEISMOVING] = true;
            if(boardGrid[player[activePlayer].row][player[activePlayer].column - 1] == SHORTCUT)
            {
                player[activePlayer].column -= 5;
                positionUpdatedX -= (18*5);
                UpdateRolledNumber(player);
            }
            else if(boardGrid[player[activePlayer].row][player[activePlayer].column - 1] != UNABLE) {
                player[activePlayer].column -= 1;
                positionUpdatedX -= 18;
                UpdateRolledNumber(player);
            }
            break;

        case KEY_S:
        case KEY_DOWN:
            gameFlags[PIECEISMOVING] = true;
            if(boardGrid[player[activePlayer].row + 1][player[activePlayer].column] == SHORTCUT)
            {
                player[activePlayer].row += 13;
                positionUpdatedY += (18*13);
                UpdateRolledNumber(player);
            }
            else if(boardGrid[player[activePlayer].row + 1][player[activePlayer].column] != UNABLE)
            {
                player[activePlayer].row += 1;
                positionUpdatedY += 18;
                UpdateRolledNumber(player);
            }
            break;

        case KEY_D:
        case KEY_RIGHT:
            gameFlags[PIECEISMOVING] = true;
            if(boardGrid[player[activePlayer].row][player[activePlayer].column + 1] == SHORTCUT)
            {
                player[activePlayer].column += 5;
                positionUpdatedX += (18*5);
                UpdateRolledNumber(player);
            }
            else if(boardGrid[player[activePlayer].row][player[activePlayer].column + 1] != UNABLE)
            {
                player[activePlayer].column += 1;
                positionUpdatedX += 18;
                UpdateRolledNumber(player);
            }
            break;
    }
}

void UpdateRolledNumber(Player players[])
{
    /*
        If the player's new position is the same as the one they had 2 movements ago, it means he took a step back.
        In which case, the rolled number increases and the movement index decreases by one, as if you didn't move
        in the first place.
     */

    players[activePlayer].movementLog[movementIndex][0] = players[activePlayer].column;
    players[activePlayer].movementLog[movementIndex][1] = players[activePlayer].row;

    if (players[activePlayer].movementLog[movementIndex][0] == players[activePlayer].movementLog[movementIndex - 2][0]
        && players[activePlayer].movementLog[movementIndex][1] == players[activePlayer].movementLog[movementIndex - 2][1])
    {
        roll++;
        movementIndex--;
        players[activePlayer].piece.resize.x = positionUpdatedX;
        players[activePlayer].piece.resize.y = positionUpdatedY;
    }
    else
    {
        roll--;
        movementIndex++;
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


void ShowAccusationInterface(Texture2D guiT[], Vector2 mouse, Texture2D sheet, Player players[], Texture2D cards)
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

    Button selectSuspects = {guiT[TGREY],
                             {0, 0},
                             {185, 469, 36, 36},
    };

    Button advertisment = {
            guiT[TGREEN],
            {GetScreenWidth()/3, GetScreenHeight() - 100},
            {0, 0, 190, 46},
            {advertisment.position.x, advertisment.position.y, advertisment.mask.width, advertisment.mask.height},
            0
    };

    Rectangle cardPlace = {
            20,
            410,
            100,
            128
    };

    DrawTexturePro(cards, (Rectangle) {1200 + (100 * GetPlayerPlace(players[activePlayer])), 0, 100, 128}, cardPlace, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawTexturePro(guiT[TGREY], (Rectangle){190, 198, 36, 36}, (Rectangle) {55, 545, 36, 36}, (Vector2) {0, 0}, 0,RAYWHITE);
    if (!gameFlags[GOINGTOHAPPEN])
        suspect.place = GetPlayerPlace(players[activePlayer]);

    for(int i = 0; i < 6; i++) {

        Rectangle cardsResizeTop = {
                20 + (150 * i),
                50,
                100,
                128
        };
        Rectangle cardsResizeMid = {
                20 + (150 * i),
                230,
                100,
                128
        };
        Rectangle cardsResizeBottom = {
                20 + (150 * i),
                410,
                100,
                128
        };

        DrawTexturePro(cards, (Rectangle) {100 * i, 0, 100, 128}, cardsResizeTop, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(cards, (Rectangle) {100 * (i + 6), 0, 100, 128}, cardsResizeMid, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(guiT[TGREY], selectSuspects.mask, (Rectangle) {55 + (150 * i), 185, 36, 36}, (Vector2) {0, 0}, 0,
                       RAYWHITE);
        DrawTexturePro(guiT[TGREY], selectSuspects.mask, (Rectangle) {55 + (150 * i), 365, 36, 36}, (Vector2) {0, 0}, 0,
                       RAYWHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, cardsResizeTop))
            {
                suspect.suspect = i + 1;
            }
            if (CheckCollisionPointRec(mouse, cardsResizeMid))
            {
                suspect.weapon = i + 7;
            }
        }
        DrawTexturePro(guiT[TGREY], (Rectangle){190, 198, 36, 36}, (Rectangle) {55 + (150 * (suspect.suspect - 1)), 185, 36, 36}, (Vector2) {0, 0}, 0,
                       RAYWHITE);
        DrawTexturePro(guiT[TGREY], (Rectangle){190, 198, 36, 36}, (Rectangle) {55 + (150 * (suspect.weapon - 7)), 365, 36, 36}, (Vector2) {0, 0}, 0,
                       RAYWHITE);

        if (gameFlags[GOINGTOHAPPEN])
        {
            // Let players make an accusation about any place regardless their position
            DrawTexturePro(cards, (Rectangle) {100 * (i + 12), 0, 100, 128}, cardsResizeBottom, (Vector2) {0, 0}, 0,
                           RAYWHITE);
            DrawTexturePro(guiT[TGREY], selectSuspects.mask, (Rectangle) {55 + (150 * i), 545, 36, 36}, (Vector2) {0, 0}, 0,
                           RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mouse, cardsResizeBottom))
                {
                    suspect.place = i + 13;
                }
            }
            DrawTexturePro(guiT[TGREY], (Rectangle){190, 198, 36, 36}, (Rectangle) {55 + (150 * (suspect.place - 13)), 545, 36, 36}, (Vector2) {0, 0}, 0,
                           RAYWHITE);
        }
    }


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
            gameFlags[SUSPECT] = false;
        }
    }
    DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);

    // Advertise suspect
    if (CheckCollisionPointRec(mouse, advertisment.collision))
    {
        advertisment.texture = guiT[TYELLOW];
        advertisment.mask = (Rectangle) {190, 0, 190, 46};
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, advertisment.collision))
        {
            if (suspect.suspect && suspect.weapon && suspect.place)
            {
                gameFlags[SUSPECT] = false;
                gameFlags[ADVERTISINGSUSPECT] = true;
            }
        }
    }
    DrawTextureRec(advertisment.texture, advertisment.mask, advertisment.position, RAYWHITE);
    DrawText("Confirmar", GetScreenWidth()/3 + 23, GetScreenHeight() - 90,  30, BLACK);

}

void ChangeTurn(Player players[])
{
    do {
        activePlayer = (activePlayer + 1) % 4;
        if (activePlayer == YELLOWPLAYER && playerCount == 3)
            activePlayer = REDPLAYER;
    } while (!players[activePlayer].inGame);
    roll = 0;
    movementIndex = 2;
    players[activePlayer].movementLog[0][0] = players[activePlayer].column;
    players[activePlayer].movementLog[1][0] = players[activePlayer].column;
    players[activePlayer].movementLog[0][1] = players[activePlayer].row;
    players[activePlayer].movementLog[1][1] = players[activePlayer].row;
    for (int i = 0; i < 14; i++)
    {
        gameFlags[i] = false;
    }
    suspect.suspect = 0;
    suspect.weapon = 0;
    suspect.place = 0;
    cardsInSuspition.suspect = 0;
    cardsInSuspition.weapon = 0;
    cardsInSuspition.place = 0;
}

bool IsSuspitionPossible(Player activeP)
{
    // Make sure suspitions are only made when player is in a place
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            if (activeP.row == 1 || activeP.row == 20)
                return true;
            if (activeP.column == 1 || activeP.column == 12)
                return true;
        }
    }
    return false;
}

bool StrongAccusation()
{
    if(gameAnswer.suspect == suspect.suspect && gameAnswer.weapon == suspect.weapon && gameAnswer.place == suspect.place)
    {
        return true;
    } else
    {
        return false;
    }
}

void StrongAccusationInterface(Texture2D guiT[], Vector2 mouse, Player players[], Texture2D profile, Rectangle masks[])
{
    Color playerColor = GetPlayerColor(activePlayer);

    Button exit = {
            guiT[TGREY],
            {GetScreenWidth() - 50, GetScreenHeight() - 50},
            {186, 433, 36, 36},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height},
            0
    };

    Picture window = {
            guiT[TGREY],
            {190, 98, 100, 100},
            {285, 50, 800, 600}
    };

    // Background transparent black screen
    DrawRectangle(0, 0, GetScreenWidth(),  GetScreenHeight(), (Color) {0, 0, 0, 125});

    DrawTexturePro(window.texture, window.mask, window.resize, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawTexturePro(profile, masks[playerId[activePlayer]], (Rectangle) {GetScreenWidth()/2 - 50, 120, 128, 128}, (Vector2) {0, 0}, 0, RAYWHITE);
    bool isStrongAccussing = StrongAccusation();

    if(isStrongAccussing)
    {
        DrawText(names[playerId[activePlayer]], GetScreenWidth()/3 + 60, GetScreenHeight()/2 + 50,  60, playerColor);
        DrawText("YOU WIN!", GetScreenWidth()/3 - 30, GetScreenHeight()/2 - 50,  120, GOLD);
    }
    else
    {
        players[activePlayer].inGame = false;

        DrawText(names[playerId[activePlayer]], GetScreenWidth()/3 + 50, GetScreenHeight()/2 + 30,  50, playerColor);
        DrawText("THE GAME IS OVER FOR YOU!", GetScreenWidth()/3 - 80, GetScreenHeight()/2 - 50,  40, GOLD);
    }

    if (CheckCollisionPointRec(mouse, exit.collision))
    {
        exit.texture = guiT[TRED];
        exit.mask = (Rectangle) {381, 36, 36, 36};
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, exit.collision))
        {
            gameFlags[ACCUSATIONHAPPENING] = false;
            ChangeTurn(players);
            if(isStrongAccussing) {
                gameFlags[GAMESHOULDCLOSE] = true;
            }
        }

    }
    DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
}

void AdvertiseSuspect(Texture2D guiT[], Vector2 mouse, Texture2D cards, Player players[], Texture2D profiles, Rectangle profilesMasks[]) {
    Picture window = {
            guiT[TGREY],
            {190, 98, 100, 100},
            {285, 50, 800, 600}
    };
    Button continueButton = {
            guiT[TBLUE],
            {0, 0},
            {0,94,190, 49},
            {600, 550, 190, 49},
            0
    };

    if (CheckCollisionPointRec(mouse, continueButton.collision))
    {
        continueButton.texture = guiT[TYELLOW];
        continueButton.mask = (Rectangle) {190, 0, 190, 46};
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, continueButton.collision))
        {
            if (gameFlags[GOINGTOHAPPEN])
            {
                gameFlags[ACCUSATIONHAPPENING] = true;
                gameFlags[ADVERTISINGSUSPECT] = false;
            }
            else if (gameFlags[SUSPECTHAPPENED])
            {
                gameFlags[ADVERTISINGSUSPECT] = false;
                gameFlags[SEARCHCARD] = false;
            }
            else if (!gameFlags[SEARCHCARD])
            {
                gameFlags[SEARCHCARD] = true;
            }
            else
            {
                gameFlags[ADVERTISINGSUSPECT] = false;
                gameFlags[REVEALCARD] = true;
            }
        }
    }

    // Background transparent black screen
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color) {0, 0, 0, 125});

    DrawTexturePro(window.texture, window.mask, window.resize, (Vector2) {0, 0}, 0, RAYWHITE);

    if (!gameFlags[SEARCHCARD])
    {
        DrawText("¡", 330, 100, 40, BLACK);
        DrawText(names[playerId[activePlayer]], 340, 100, 40, GetPlayerColor(activePlayer));
        if (gameFlags[GOINGTOHAPPEN])
            DrawText(" ha hecho una acusación!", 320, 150, 40, BLACK);
        else
            DrawText(" ha hecho una sospecha!", 320, 150, 40, BLACK);
        for (int i = 0; i < 3; i++)
        {
            DrawTexturePro(cards, (Rectangle) {100 * (suspect.suspect - 1), 0, 100, 128}, (Rectangle) {400, 225, 150, 192}, (Vector2) {0, 0}, 0, RAYWHITE);
            DrawTexturePro(cards, (Rectangle) {100 * (suspect.weapon - 1), 0, 100, 128}, (Rectangle) {600, 225, 150, 192}, (Vector2) {0, 0}, 0, RAYWHITE);
            DrawTexturePro(cards, (Rectangle) {100 * (suspect.place - 1), 0, 100, 128}, (Rectangle) {800, 225, 150, 192}, (Vector2) {0, 0}, 0, RAYWHITE);
        }
    }
    else
    {
        int playerWithSuspects = FindPlayerWithSuspects(players);
        if (playerWithSuspects != activePlayer)
        {
            DrawTexturePro(profiles, profilesMasks[playerId[playerWithSuspects]], (Rectangle) {350, 200, 128, 128}, (Vector2) {0, 0}, 0, RAYWHITE);
            DrawText(names[playerId[playerWithSuspects]], 350, 350, 35, GetPlayerColor(playerWithSuspects));
            DrawText("tiene al menos una carta de la sospecha,", 350, 390, 30, BLACK);
            DrawText("Pasa el dispositivo para que revele una carta", 350, 430, 28, BLACK);
        }
        else
        {
            gameFlags[SUSPECTHAPPENED] = true;
            DrawText("Parece que nadie tiene cartas de tu sospecha", 330, 350, 30, BLACK);
            DrawText("Presiona el botón de acusar si quieres convertir", 330, 390, 30, BLACK);
            DrawText("tu sospecha en acusación", 330, 430, 30, BLACK);
        }
    }
    DrawTexturePro(continueButton.texture, continueButton.mask, continueButton.collision, (Vector2) {0, 0}, 0, RAYWHITE);
    DrawText("Continuar", 620, 560, 30, BLACK);
}

int FindPlayerWithSuspects(Player players[])
{
    int playerWithSuspects = (activePlayer + 1) % 4;
    bool playerHasCards = false;

    for (int i = 0; i < playerCount - 1; i++)
    {
        if (players[playerWithSuspects].inGame)
        {
            for (int k = 0; k < 3; k++)
            {
                if (players[playerWithSuspects].cards[k] == suspect.suspect)
                {
                    cardsInSuspition.suspect = players[playerWithSuspects].cards[k];
                    playerHasCards = true;
                }
                if (players[playerWithSuspects].cards[k] == suspect.weapon)
                {
                    cardsInSuspition.weapon = players[playerWithSuspects].cards[k];
                    playerHasCards = true;
                }
                if (players[playerWithSuspects].cards[k] == suspect.place)
                {
                    cardsInSuspition.place = players[playerWithSuspects].cards[k];
                    playerHasCards = true;
                }
            }
            if (playerHasCards)
                return playerWithSuspects;
            playerWithSuspects = (playerWithSuspects + 1) % 4;
        }
    }
    return activePlayer;
}

void RevealCardInterface(Player players[], Texture2D guiT[], Texture2D cards, Vector2 mouse)
{
    Picture window = {
            guiT[TGREY],
            {190, 98, 100, 100},
            {285, 50, 800, 600}
    };

    // Background transparent black screen
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color) {0, 0, 0, 125});

    DrawTexturePro(window.texture, window.mask, window.resize, (Vector2) {0, 0}, 0, RAYWHITE);

    DrawText("Escoge una carta para revelar", 350, 200, 30, BLACK);
    DrawText("La carta se añadira al inventario de", 350, 500, 20, BLACK);
    DrawText(names[playerId[activePlayer]], 350, 530, 20, GetPlayerColor(activePlayer));

    int Cards[] = {cardsInSuspition.suspect, cardsInSuspition.weapon, cardsInSuspition.place};

    for (int i = 0; i < 3; i++)
    {
        if (Cards[i] != NULLCARD)
        {
            DrawTexturePro(cards, (Rectangle) {100 * (Cards[i] - 1), 0, 100, 128}, (Rectangle) {400 + (200 * i), 250, 150, 192}, (Vector2) {0, 0}, 0, RAYWHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mouse, (Rectangle) {400 + (200 * i), 250, 150, 192}))
                {
                    RevealCard(Cards[i]);
                    gameFlags[REVEALCARD] = false;
                    ChangeTurn(players);
                    return;
                }
            }
        }

    }
}

void RevealCard(int card)
{
    playersNotes[activePlayer][card - 1] = 1;
}

int GetPlayerPlace(Player player)
{
    int place;
    if (player.column == 1)
    {
        if (player.row > 10)
            place = MLIVING;
        else
            place = MLIBRARY;
    }
    else if (player.column == 11)
    {
        if (player.row > 11)
            place = MBEDROOM;
        else
            place = MKITCHEN;
    }
    else
    {
        if (player.row == 1)
            place = MBATHROOM;
        else
            place = MGARAGE;
    }
    return place - 3;
}

Color GetPlayerColor(int player)
{
    switch (player) {
        case REDPLAYER: return MAROON;
        case BLUEPLAYER: return DARKBLUE;
        case GREENPLAYER: return DARKGREEN;
        case YELLOWPLAYER: return GOLD;
        default: return GRAY;
    }
}