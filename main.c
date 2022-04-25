#include "raylib.h"
#include "PlayerRelated.h"
#include "Animations.h"
#include "Windows.h"
#include "GamePlay.h"

int main()
{
    SetTargetFPS(30);
    MainWindow();
    if (playerCount)
        Gameplay();
    return 0;
}