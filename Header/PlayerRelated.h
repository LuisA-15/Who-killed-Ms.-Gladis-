typedef struct player_struct {
    int posx;
    int posy;
    int cards[5];
} Player;

enum players {
    REDPLAYER,
    BLUEPLAYER,
    GREENPLAYER,
    YELLOWPLAYER
};

int playerCount = 0;
// Each playable character has an id that matches with its index in the names array. These are the default values
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