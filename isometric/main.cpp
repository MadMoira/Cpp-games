#include <iostream>
#include "raylib.h"
#include <cmath>
#include <string>

int main() {

    const int screenWidth = 1000;
    const int screenHeight = 600;

    SetConfigFlags(32);
    InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Texture2D tiles = LoadTexture("assets/tiles.png");
    Vector2 vWorldSize = {14, 10};
    Vector2 vTileSize = {64, 32};
    Vector2 vOrigin = {5, 1};
    int *pWorld = new int[(int)vWorldSize.x * (int)vWorldSize.y]{ 0 };
    auto imgData = GetTextureData(tiles);
    auto colorData = GetImageData(imgData);

    auto* position = new Vector2{200, 200};

    while(!WindowShouldClose()) {

        Vector2 mousePos = {(float)GetMouseX(), (float)GetMouseY()};
        Vector2 vCell = {
                static_cast<float>(std::trunc(mousePos.x / vTileSize.x)),
                static_cast<float>(std::trunc(mousePos.y / vTileSize.y))
        };
        Vector2 vOffset = {
                static_cast<float>(std::fmod(mousePos.x, vTileSize.x)),
                static_cast<float>(std::fmod(mousePos.y, vTileSize.y))
        };
        int idx = ((42 + (int)vOffset.y) * 3 * (int)vTileSize.x) + (2 * (int)vTileSize.x) + (int)vOffset.x;
        Color pixel = colorData[idx];

        Vector2 vSelected =
        {
                (vCell.y - vOrigin.y) + (vCell.x - vOrigin.x),
                (vCell.y - vOrigin.y) - (vCell.x - vOrigin.x),
        };

        bool inBounds = vSelected.x >= 0 && vSelected.x < vWorldSize.x && vSelected.y >= 0 && vSelected.y < vWorldSize.y;

        if (pixel.r == 255 && pixel.b == 0) vSelected.x += -1;
        if (pixel.r == 0 && pixel.b == 255) vSelected.y += -1;
        if (pixel.g == 255) vSelected.y += +1;
        if (pixel.r == 255 && pixel.b == 255) vSelected.x += 1;

        if (inBounds) {
            if(IsKeyPressed(KEY_ONE)) pWorld[(int)(vWorldSize.x * vSelected.y + vSelected.x)] = 1;
            if(IsKeyPressed(KEY_TWO)) pWorld[(int)(vWorldSize.x * vSelected.y + vSelected.x)] = 2;
            if(IsKeyPressed(KEY_THREE)) pWorld[(int)(vWorldSize.x * vSelected.y + vSelected.x)] = 3;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto ToScreen = [&](int x, int y) {
            return Vector2 {
                    (vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
                    (vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2),
            };
        };

        for (int y = 0; y < (int)vWorldSize.y; y++) {
            for (int x = 0; x < (int)vWorldSize.x; x++) {

                Vector2 vWorld = ToScreen(x, y);

                switch (pWorld[y*(int)vWorldSize.x + x]) {
                    case 0:
                        DrawTextureRec(tiles, Rectangle{64, 42, 64, 32}, vWorld, WHITE);
                        break;
                    case 1:
                        DrawTextureRec(tiles, Rectangle{0, 0, 64, 42}, vWorld, WHITE);
                        break;
                    case 2:
                        DrawTextureRec(tiles, Rectangle{64, 0, 64, 42}, vWorld, WHITE);
                        break;
                    case 3:
                        DrawTextureRec(tiles, Rectangle{128, 0, 64, 42}, vWorld, WHITE);
                        break;
                }
            }
        }

        if (inBounds) {
            Vector2 vSelectedWorld = ToScreen(vSelected.x, vSelected.y);
            DrawTextureRec(tiles, Rectangle{0, 42, 64, 32}, vSelectedWorld, WHITE);
        }

        auto mouseMsg = "Mouse: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
        auto cellMsg = "Cell: " + std::to_string(vCell.x) + ", " + std::to_string(vCell.y);
        auto selectedMsg = "Selected: " + std::to_string(vSelected.x) + ", " + std::to_string(vSelected.y);
        DrawText(mouseMsg.c_str(), 20, 20, 10, RED);
        DrawText(cellMsg.c_str(), 20, 40, 10, RED);
        DrawText(selectedMsg.c_str(), 20, 60, 10, RED);

        EndDrawing();
    }

    UnloadTexture(tiles);
    CloseWindow();
    delete position;

    return 0;
}
