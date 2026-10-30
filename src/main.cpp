#include <raylib.h>
#include "player.h"
#include "camera.h"

int main()
{
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "8 Direction Prototype");
    SetTargetFPS(144);

    // Player origin location
    Player player({0.0f, 0.0f});

    // Camera centered on player
    GameCamera gameCamera(player.getPosition(), 1.0f);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Update player
        player.update(deltaTime);

        // Update camera to follow player
        gameCamera.followTarget(player.getPosition(), deltaTime);

        // Zoom controls
        if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD))
            gameCamera.setZoom(1.5f); // Zoom in
        if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT))
            gameCamera.setZoom(1.0f); // Zoom out

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Draw world with camera
        gameCamera.begin();
        {
            // Draw player
            player.draw(1.0f);
        }
        gameCamera.end();

        DrawFPS(10, 10);

        Vector2 playerPos = player.getPosition();
        DrawText(TextFormat("Position: (%.0f, %.0f)", playerPos.x, playerPos.y),
                 10, 30, 20, WHITE);

        DrawText("Controls: WASD - Move | SHIFT - Run",
                 10, screenHeight - 30, 20, WHITE);
        DrawText("[+/-] Zoom In/Out",
                 10, screenHeight - 55, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
