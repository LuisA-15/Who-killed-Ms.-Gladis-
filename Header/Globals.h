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
    SUSPECT,
    DICEISROLLING,
    DICEWASROLLED,
    PIECEISMOVING,
    OPENCONFIRMEXIT,
    GAMESHOULDCLOSE,
    GAMESHOULDRESTART
};

void CreateBoard();
void RestartValues(int PlayerCount);

Accusation gameAnswer;

// Flags to change game flow
bool gameFlags[10] = {};


// Player related

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

Player redPlayer = {18, 5, .piece.mask = (Rectangle){0, 0, 15, 17},
                    .piece.resize = (Rectangle){620, 465, 15, 17}};
Player bluePlayer = {18, 6};
Player greenPlayer = {18, 7};
Player yellowPlayer= {18, 8};

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
float musicVolume = 0.0;
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


void RestartValues(int PlayerCount)
{
    playerCount = PlayerCount;
    activePlayer = REDPLAYER;
    redPlayer.row = 18;
    redPlayer.column = 5;
    bluePlayer.row = 18;
    bluePlayer.column = 6;
    greenPlayer.row = 18;
    greenPlayer.column = 7;
    yellowPlayer.row = 18;
    yellowPlayer.column = 8;

    for (int i = 0; i < 4; i++)
    {
        for (int k = 0; k < 18; k++)
            playersNotes[i][k] = 0;
    }

    roll = 0;

    for (int i = 0; i < 10; i++)
    {
        gameFlags[i] = false;
    }
}