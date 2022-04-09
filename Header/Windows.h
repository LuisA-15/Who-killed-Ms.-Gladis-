typedef struct button_struct {
    Texture2D texture;
    Vector2 position;
    Rectangle mask;
    Rectangle collision;
}Button;

void MainWindow();


void MainWindow()
{
    InitWindow(600, 500, "Clue Sus");
    Vector2 mousePoint;

    Texture2D TBLUE = LoadTexture("C:/Users/Luis/CLionProjects/ClueSus/Assets/blueSheet.png");
    Texture2D TYELLOW = LoadTexture("C:/Users/Luis/CLionProjects/ClueSus/Assets/yellowSheet.png");
    Texture2D TRED = LoadTexture("C:/Users/Luis/CLionProjects/ClueSus/Assets/redSheet.png");

    Button start = {
            TBLUE,
            {225, 200},
            {0,94,190, 49},
            {start.position.x, start.position.y, start.mask.width, start.mask.height}
    };
    Button exit = {
            TRED,
            {225, 280},
            {190, 0, 190, 49},
            {exit.position.x, exit.position.y, exit.mask.width, exit.mask.height}
    };


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("CLUE SUS", 150, 100, 60, BLACK);

        DrawTextureRec(start.texture, start.mask, start.position, WHITE);
        DrawText("Jugar", 280, 205, 30, BLACK);

        DrawTextureRec(exit.texture, exit.mask, exit.position, WHITE);
        DrawText("Salir", 290, 290, 30, BLACK);

        if (IsMouseButtonPressed(0))
        {
            mousePoint = GetMousePosition();

            if (CheckCollisionPointRec(mousePoint, start.collision))
            {
                ClearBackground(BLACK);
            }
            else if (CheckCollisionPointRec(mousePoint, exit.collision))
            {
                EndDrawing();
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}