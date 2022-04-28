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
    int posx;
    int posy;
    int cards[6];
} Player;

typedef struct accusation_struct {
    int suspect;
    int weapon;
    int place;
} Accusation;

enum texture_names {
    TBLUE,
    TYELLOW,
    TRED,
    TGREEN,
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

Player redPlayer;
Player bluePlayer;
Player greenPlayer;
Player yellowPlayer;

Accusation gameAnswer;

int boardGrid[20][10] = {};