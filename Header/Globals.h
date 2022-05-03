typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
    int status; // 1 if pressed, 0 if not
} Button;

typedef struct picture_struct {
    Texture2D texture;
    Rectangle mask;
    Rectangle resize;
} Picture;

typedef struct player_struct {
    int row;
    int column;
    int cards[6];
} Player;

typedef struct accusation_struct {
    int suspect;
    int weapon;
    int place;
} Accusation;

enum texture_names {
    TRED,
    TBLUE,
    TGREEN,
    TYELLOW,
    TGREY
};

enum players {
    REDPLAYER,
    BLUEPLAYER,
    GREENPLAYER,
    YELLOWPLAYER
};

enum cards_enum {
    NULLCARD,
    MARYPOPPINS, CORNELIUS, KIM, JOEL, HILDA, MAX,
    KNIFE, GUN, POISON, PANTIES, JAR, STEAK,
    LIVING, LIBRARY, BATHROOM, KITCHEN, BEDROOM, GARAGE,
};

enum items_enum {
    NOTES,
    CASEFILE,
    NOTESSELECTED
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

enum flags_enum {
    SHOWCARDS,
    OPTIONS,
    REVEALCARD,
    SUSPECT,
    OPENCONFIRMEXIT,
    GAMESHOULDCLOSE,
    GAMESHOULDRESTART
};

void CreateBoard();
void RestartValues(int PlayerCount);

// Flags to change game flow
bool gameFlags[7] = {};

float musicVolume = 0.0;

int playerCount = 0;
int playerId[] = {0, 1, 2, 3};

char names[][15] = {
        "Mary Poppins",
        "Cornelius",
        "Kim",
        "Joel",
        "Hilda",
        "Max",
        ""
};

Player redPlayer = {18, 6};
Player bluePlayer = {18, 8};
Player greenPlayer = {19, 6};
Player yellowPlayer= {19, 8};

int activePlayer = REDPLAYER; // First player in turn order by default

int playersNotes[4][18] = {};

Accusation gameAnswer;

int boardGrid[22][12] = {};

void CreateBoard()
{
    for (int i = 0; i < 12; i++)
    {
        boardGrid[0][i] = UNABLE;
        boardGrid[1][i] = UNABLE;
        boardGrid[20][i] = UNABLE;
        boardGrid[21][i] = UNABLE;
        boardGrid[i][0] = UNABLE;
        boardGrid[i][1] = UNABLE;
        boardGrid[i][10] = UNABLE;
        boardGrid[i][11] = UNABLE;
        boardGrid[i + 12][0] = UNABLE;
        boardGrid[i + 12][1] = UNABLE;
        boardGrid[i + 9][10] = UNABLE;
        boardGrid[i + 9][11] = UNABLE;
    }
    for (int i = 5; i < 17; i++)
    {
        boardGrid[i][5] = UNABLE;
        boardGrid[i][6] = UNABLE;
    }
    for (int i = 0; i < 4; i++)
    {
        boardGrid[i + 12][1] = MLIVING;
        boardGrid[i + 4][1] = MLIBRARY;
        boardGrid[1][i + 4] = MBATHROOM;
        boardGrid[i + 4][10] = MKITCHEN;
        boardGrid[i + 12][10] = MBEDROOM;
        boardGrid[20][i + 4] = MGARAGE;
    }
    for (int i = 4; i < 8; i++)
    {
        boardGrid[4][i] = SHORTCUT;
        boardGrid[17][i] = SHORTCUT;
        boardGrid[i][4] = SHORTCUT;
        boardGrid[i + 4][4] = SHORTCUT;
        boardGrid[i + 8][4] = SHORTCUT;
        boardGrid[i][7] = SHORTCUT;
        boardGrid[i + 4][7] = SHORTCUT;
        boardGrid[i + 8][7] = SHORTCUT;
    }
    boardGrid[16][4] = SHORTCUT;
    boardGrid[16][7] = SHORTCUT;
}

void RestartValues(int PlayerCount)
{
    playerCount = PlayerCount;
    activePlayer = REDPLAYER;
    redPlayer.row = 18;
    redPlayer.column = 6;
    bluePlayer.row = 18;
    bluePlayer.column = 8;
    greenPlayer.row = 19;
    greenPlayer.column = 6;
    yellowPlayer.row = 19;
    yellowPlayer.column = 8;

    for (int i = 0; i < 4; i++)
    {
        for (int k = 0; k < 18; k++)
            playersNotes[i][k] = 0;
    }

    for (int i = 0; i < 7; i++)
    {
        gameFlags[i] = false;
    }
}