#include "raylib.h"
#include "stdio.h"


Sprite LoadSprite(const char *filename, int frameCount);
SpriteGraphics LoadSpriteGraphics(const char *filename, int frameCount, float refresh);
SpriteGraphics UpdateSpriteGraphic(SpriteGraphics g);
void UpdatePosition(Player players[]);

Sprite LoadSprite(const char *filename, int frameCount)
{
    Texture2D texture = LoadTexture(filename);
    Sprite s = {
            texture,
            {0, 0, texture.width / frameCount, texture.height},
            frameCount
    };
    return s;
}

SpriteGraphics LoadSpriteGraphics(const char *filename, int frameCount, float refresh)
{
    SpriteGraphics g = {
            LoadSprite(filename, frameCount), 0, 0, refresh
    };
    return g;
}

SpriteGraphics UpdateSpriteGraphic(SpriteGraphics g)
{
    float elapsed = GetFrameTime();
    g.deltaTime += elapsed;

    if(g.deltaTime >= g.refreshRate)
    {
        g.deltaTime = 0;
        g.currentFrame = (g.currentFrame + 1) % g.sprite.frameCount;
        g.sprite.mask.x = g.sprite.mask.width * g.currentFrame;
    }

    return g;
}

void RollDice(float time)
{
    if (!roll)
        roll = GetRandomValue(1, 6);
    if (time <= 1.5)
    {
        DrawTextureRec(rollingDice.sprite.texture, rollingDice.sprite.mask, (Vector2) {1050, 15}, RAYWHITE);

        float elapsed = GetFrameTime();
        rollingDice.deltaTime += elapsed;

        if(rollingDice.deltaTime >= rollingDice.refreshRate)
        {
            rollingDice.deltaTime = 0;
            rollingDice.currentFrame = (rollingDice.currentFrame + 1) % rollingDice.sprite.frameCount;
            rollingDice.sprite.mask.x = rollingDice.sprite.mask.width * rollingDice.currentFrame;
        }
    }
    else
    {
        gameFlags[DICEISROLLING] = false;
        gameFlags[DICEWASROLLED] = true;
    }
}

void UpdatePosition(Player players[]) {
    int currentX = players[activePlayer].movementLog[movementIndex - 1][0];
    int currentY = players[activePlayer].movementLog[movementIndex - 1][1];
    int pastX = players[activePlayer].movementLog[movementIndex - 2][0];
    int pastY = players[activePlayer].movementLog[movementIndex - 2][1];

    int deltax = currentX - pastX;
    int deltay = currentY - pastY;

    if (players[activePlayer].piece.resize.y != positionUpdatedY) {
        players[activePlayer].piece.resize.y += deltay;
        DrawTexturePro(players[activePlayer].piece.texture, players[activePlayer].piece.mask, players[activePlayer].piece.resize, (Vector2){0,0}, 0, RAYWHITE);
    }


    if (players[activePlayer].piece.resize.x != positionUpdatedX) {
        players[activePlayer].piece.resize.x += deltax;
        DrawTexturePro(players[activePlayer].piece.texture, players[activePlayer].piece.mask, players[activePlayer].piece.resize, (Vector2){0,0}, 0, RAYWHITE);
    }

    if(players[activePlayer].piece.resize.y == positionUpdatedY && players[activePlayer].piece.resize.x == positionUpdatedX)
    {
        gameFlags[PIECEISMOVING] = false;
        DrawTexturePro(players[activePlayer].piece.texture, players[activePlayer].piece.mask, players[activePlayer].piece.resize, (Vector2){0,0}, 0, RAYWHITE);
    }
}