#include "raylib.h"
#include "stdio.h"

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


Sprite LoadSprite(const char *filename, int frameCount);
SpriteGraphics LoadSpriteGraphics(const char *filename, int frameCount, float refresh);
SpriteGraphics UpdateSpriteGraphic(SpriteGraphics g);
Piece UpdatePosition(Picture current, int x, int y);


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

Piece UpdatePosition(Picture current, int x, int y) {
    float time = 0;
    int positionUpdatedX = current.resize.x + (x * 18);
    int positionUpdatedY = current.resize.y + (y * 18);

    while (current.resize.y < positionUpdatedY) {
        //if (time >= 0.2) {
            current.resize.y += y;
    //    }
        DrawTexturePro(current.texture, current.mask, current.resize, (Vector2){0,0}, 0, RAYWHITE);
        time += GetFrameTime();
    }
    while (current.resize.x < positionUpdatedX) {
    //    if (time >= 0.2) {
            current.resize.x += x;
    //    }
        DrawTexturePro(current.texture, current.mask, current.resize, (Vector2){0,0}, 0, RAYWHITE);
        time += GetFrameTime();
    }
    printf("(%f, %f)", current.resize.x, current.resize.y);
}