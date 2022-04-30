#include "raylib.h"
#include "Globals.h"
#include "Animations.h"
#include "Windows.h"
#include "GamePlay.h"

int main()
{
    SetTargetFPS(30);
    InitAudioDevice();
    MainWindow();
    if (playerCount)
        Gameplay();
    CloseAudioDevice();
    return 0;
}
