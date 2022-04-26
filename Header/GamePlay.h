typedef struct accusation_struct {
    int suspect;
    int weapon;
    int place;
} Accusation;

enum cards_enum {
    NULLCARD,
    MARYPOPPINS, CORNELIUS, KIM, JOEL, HILDA, MAX,
    KNIFE, GUN, POISON, PANTIES, JAR, STEAK,
    LIVING, LIBRARY, BATHROOM, KITCHEN, BEDROOM, GARAGE,
};

enum items_enum {
    NOTES,
    CASEFILE
};

enum movements_enum {
    ABLE,
    UNABLE,
    SHORTCUT,
    MLIVING,
    MLIBRARY,
    MBATHROOM,
    MKITCHEN,
    MBEDROOM,
    MGARAGE
};

Accusation gameAnswer;

void Gameplay();
int SortCards(int cardsInUse[18], int index);
void AssignCards(Player players[], int cardsInUse[]);

void Gameplay() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Who killed Mrs. Gladys?");
    MaximizeWindow();
    Vector2 mousePoint;

    Texture2D board = LoadTexture("../Assets/board/board.png");

    Texture2D TBlue = LoadTexture("../Assets/blueSheet.png");
    Texture2D TYellow = LoadTexture("../Assets/yellowSheet.png");
    Texture2D TRed = LoadTexture("../Assets/redSheet.png");
    Texture2D TGreen = LoadTexture("../Assets/greenSheet.png");
    Texture2D TGrey = LoadTexture("../Assets/greysheet.png");
    Texture2D guiTextures[] = {TBlue, TYellow, TRed, TGreen, TGrey};

    Texture2D items = LoadTexture("../Assets/item icons.png");
    Rectangle knifeMask = {0, 0, 70, 70};
    Rectangle gunMask = {items.width / 8, 0, 70, 70};
    Rectangle poisonMask = {items.width * 2 / 8, 0, 70, 70};
    Rectangle pantiesMask = {items.width * 3 / 8, 0, 70, 70};
    Rectangle jarMask = {items.width * 4 / 8, 0, 70, 70};
    Rectangle steakMask = {items.width * 5 / 6, 0, 70, 70};
    Rectangle cardMasks[] = {knifeMask, gunMask, poisonMask, pantiesMask, jarMask, steakMask};

    Rectangle notesMask = {items.width * 6 / 8, 0, 70, 70};
    Rectangle casefileMask = {items.width * 7 / 8, 0, 70, 70};
    Rectangle itemsMasks[] = {notesMask, casefileMask};

    Texture2D notesSheet = LoadTexture("../Assets/notesSheet.png");

    Texture2D profilePics = LoadTexture("../Assets/charProfiles.png");
    Rectangle gladisMask = {0, 0, 64, 64};
    Rectangle kimMask = {profilePics.width / 6, 0, 64, 64};
    Rectangle hildaMask = {(profilePics.width * 2) / 6, 0, 64, 64};
    Rectangle colonelMask = {(profilePics.width * 3) / 6, 0, 64, 64};
    Rectangle boyMask = {(profilePics.width * 4) / 6, 0, 64, 64};
    Rectangle detectiveMask = {(profilePics.width * 5) / 6, 0, 64, 64};
    Rectangle profileMasks[] = {gladisMask, colonelMask, kimMask, boyMask, hildaMask, detectiveMask};

    int boardGrid[20][10] = {};

    int activePlayer = REDPLAYER; // First player in turn order by default

    Player players[] = {redPlayer, bluePlayer, greenPlayer, yellowPlayer};

    gameAnswer.suspect = GetRandomValue(MARYPOPPINS, MAX);
    gameAnswer.weapon = GetRandomValue(KNIFE, STEAK);
    gameAnswer.place = GetRandomValue(LIVING, GARAGE);
    int sortedCards[18] = {gameAnswer.suspect, gameAnswer.weapon, gameAnswer.place};

    for (int i = 2; i < 18; i++)
        sortedCards[i] = SortCards(sortedCards, i);
    AssignCards(players, sortedCards);
    if (playerCount == 4) {
        int unusedCards[3] = {sortedCards[15], sortedCards[16], sortedCards[17]};
    }
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBROWN);
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

        // Active Player marker
        DrawRectangle(10, 35 + (160 * activePlayer), 20, 138, YELLOW);

//        DrawTextureRec(notesSheet, (Rectangle) {0, 0, notesSheet.width, notesSheet.height}, (Vector2) {0, 0}, RAYWHITE);

        // Draw Action buttons
        DrawTexturePro(guiTextures[TBLUE], (Rectangle) {0,94,190, 49}, (Rectangle) {1050, 350, 380, 90}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(guiTextures[TGREEN], (Rectangle) {0, 0,190, 49}, (Rectangle) {1050, 450, 380, 90}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(guiTextures[TRED], (Rectangle) {190, 0, 190, 49}, (Rectangle) {1050, 550, 380, 90}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawTexturePro(guiTextures[TGREY], (Rectangle) {0, 237, 190, 49}, (Rectangle) {1200, 650, 190, 49}, (Vector2) {0, 0}, 0, RAYWHITE);
        DrawText("Tirar dado", 1080, 365, 50, BLACK);
        DrawText("Sospechar", 1080, 465, 50, BLACK);
        DrawText("Acusar", 1130, 565, 50, BLACK);
        DrawText("Opciones", 1220, 660, 30, BLACK);


//        DrawRectangle(0, 0, 1000, 900, (Color) {0, 0, 0, 100});

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

void AssignCards(Player players[], int cardsInUse[])
{
    int cardsForEachPlayer = 5;
    if (playerCount == 4)
        cardsForEachPlayer = 3;

    for (int player = REDPLAYER; player <= YELLOWPLAYER; player++)
    {
        for (int i = 0; i < cardsForEachPlayer; i++)
            players[player].cards[i] = cardsInUse[3 * (player + 1) + i];
    }
}

