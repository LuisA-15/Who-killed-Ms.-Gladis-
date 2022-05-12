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

typedef struct sprite_struct
{
    Texture2D texture;
    Rectangle mask;
    int frameCount;
}Sprite;

typedef struct sprite_graphics_struct
{
    Sprite sprite;
    int currentFrame;
    float deltaTime;
    float refreshRate;
}SpriteGraphics;

typedef struct player_struct {
    int row;
    int column;
    int cards[6];
    int movementLog[8][2];
    Picture piece;
    bool inGame;
} Player;

typedef struct accusation_struct {
    int suspect;
    int weapon;
    int place;
} Accusation;

typedef struct player_piece_struct{
    Player PlayerPiece;
    Picture piece;
} Piece;

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
    SEARCHCARD,
    ADVERTISINGSUSPECT,
    SUSPECT,
    SUSPECTHAPPENED,
    DICEISROLLING,
    DICEWASROLLED,
    PIECEISMOVING,
    OPENCONFIRMEXIT,
    GOINGTOHAPPEN,
    ACCUSATIONHAPPENING,
    GAMESHOULDCLOSE,
    GAMESHOULDRESTART
};

void CreateBoard();
void RestartValues(Player players[]);

/*
    - Game solution
    - Suspition proposoed by the player in turn
    - Cards the next player has with the actual suspition being made
 */
Accusation gameAnswer;
Accusation suspect = {NULLCARD, NULLCARD, NULLCARD};
Accusation cardsInSuspition = {NULLCARD, NULLCARD, NULLCARD};

// Flags to change game flow
bool gameFlags[15] = {};

// Player related

int playerCount = 4;
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


Player redPlayer = {18, 5,
        .piece.mask = (Rectangle){0, 0, 15, 17},
        .piece.resize = (Rectangle){620, 465, 15, 17},
        .inGame = true};
Player bluePlayer = {18, 6,
        .piece.mask = (Rectangle){0, 17, 15, 15},
        .piece.resize = (Rectangle){638, 465, 15, 15},
        .inGame = true};
Player greenPlayer = {18, 7,
        .piece.mask = (Rectangle){0, 32,15, 16},
        .piece.resize = (Rectangle){654, 465, 15, 16},
        .inGame = true};
Player yellowPlayer= {18, 8,
        .piece.mask = (Rectangle){0, 48, 15, 16},
        .piece.resize = (Rectangle){672, 465, 15, 16},
        .inGame = true};




int activePlayer = REDPLAYER; // First player in turn order by default
int playersNotes[4][18] = {};

int movementIndex = 2;
int positionUpdatedX;
int positionUpdatedY;

// Dice related

int roll = 0;
SpriteGraphics rollingDice = {
        {
                .mask = {0, 0, 260, 260},
                16
        },
        0,
        0,
        0.025
};

// Music related

int nowPlaying;
float musicVolume = 0.6;
Music bgMusic[2];
char bgMusicNames[][50] = {
        "When the Moons Reaching Out Stars",
        "Air theme"
};
char bgMusicPaths[][100] = {
        "../Assets/Sounds/Persona 3 OST  When the Moons Reaching Out Stars.mp3",
        "../Assets/Sounds/airtheme.mp3"
};


// Board related

int boardGrid[22][14] = {};
void CreateBoard()
{
    for (int i = 0; i < 14; i++)
    {
        boardGrid[0][i] = UNABLE;
        boardGrid[1][i] = UNABLE;
        boardGrid[20][i] = UNABLE;
        boardGrid[21][i] = UNABLE;

        boardGrid[i][0] = UNABLE;
        boardGrid[i][1] = UNABLE;
        boardGrid[i][12] = UNABLE;
        boardGrid[i][13] = UNABLE;
        boardGrid[i + 6][0] = UNABLE;
        boardGrid[i + 6][1] = UNABLE;
        boardGrid[i + 6][12] = UNABLE;
        boardGrid[i + 6][13] = UNABLE;
    }

    for (int i = 0; i < 12; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            boardGrid[5 + i][5 + k] = SHORTCUT;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        boardGrid[14 + i][1] = MLIVING;
        boardGrid[6 + i][1] = MLIBRARY;
        boardGrid[1][4 + i] = MBATHROOM;
        boardGrid[7 + i][12] = MKITCHEN;
        boardGrid[16 + i][12] = MBEDROOM;
        boardGrid[20][6 + i] = MGARAGE;
    }
}

void RestartValues(Player players[])
{
    roll = 0;
    activePlayer = REDPLAYER;

    for (int i = REDPLAYER; i <= YELLOWPLAYER; i++)
    {
        players[i].inGame = true;
        players[i].row = 18;
        players[i].column = 5 + i;
        for (int k = 0; k < 18; k++)
            playersNotes[i][k] = 0;
    }
    redPlayer.piece.resize = (Rectangle){620, 465, 15, 17},
    bluePlayer.piece.resize = (Rectangle){638, 465, 15, 15},
    greenPlayer.piece.resize = (Rectangle){654, 465, 15, 16},
    yellowPlayer.piece.resize = (Rectangle){672, 465, 15, 16},
    suspect.suspect = 0;
    suspect.weapon = 0;
    suspect.place = 0;
    cardsInSuspition.suspect = 0;
    cardsInSuspition.weapon = 0;
    cardsInSuspition.place = 0;

    for (int i = 0; i < 15; i++)
    {
        gameFlags[i] = false;
    }
}