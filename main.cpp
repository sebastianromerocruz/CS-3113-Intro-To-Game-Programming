#include "raylib.h"
#include <iostream>

enum AppStatus { RUNNING, TERMINATED };

constexpr int WINDOW_WIDTH  = 640 * 2;
constexpr int WINDOW_HEIGHT = 480 * 2;

constexpr char SHIELD_SPRITE_FILEPATH[] = "assets/shield.png";
constexpr float INIT_SCALE_X = 0.5f;
constexpr float INIT_SCALE_Y = 0.599625f;
constexpr float g_shield_speed = 5.0f;  // move 1 unit per second

AppStatus g_app_status = RUNNING;

Texture2D g_shield_texture;

Vector2 g_shield_position = { 0.0f, 0.0f };
Vector2 g_shield_movement = { 0.0f, 0.0f };

void initialise()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, Player Input!");

    // Load texture
    g_shield_texture = LoadTexture(SHIELD_SPRITE_FILEPATH);

    // Set the target FPS
    SetTargetFPS(60);
}

void process_input()
{
    if (IsKeyPressed(KEY_ESCAPE)) {
        g_app_status = TERMINATED;
    }

    // Update movement based on keyboard input (e.g., WASD or arrow keys)
    g_shield_movement = (Vector2){0.0f, 0.0f};
    if (IsKeyDown(KEY_W)) g_shield_movement.y -= 1.0f;
    if (IsKeyDown(KEY_S)) g_shield_movement.y += 1.0f;
    if (IsKeyDown(KEY_A)) g_shield_movement.x -= 1.0f;
    if (IsKeyDown(KEY_D)) g_shield_movement.x += 1.0f;
}

void update()
{
    /* DELTA TIME */
    float delta_time = GetFrameTime();

    /* GAME LOGIC */
    g_shield_position.x += g_shield_movement.x * g_shield_speed * delta_time;
    g_shield_position.y += g_shield_movement.y * g_shield_speed * delta_time;
}

void render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the shield texture
    DrawTextureEx(g_shield_texture, (Vector2) { 
        (float) (WINDOW_WIDTH / 2 + g_shield_position.x * 50.0f - (g_shield_texture.width * INIT_SCALE_X / 2)),
        (float) (WINDOW_HEIGHT / 2 + g_shield_position.y * 50.0f - (g_shield_texture.height * INIT_SCALE_Y / 2))
    }, 0.0f, INIT_SCALE_X, WHITE);

    EndDrawing();
}

void shutdown()
{
    UnloadTexture(g_shield_texture);
    CloseWindow();
}

int main()
{
    initialise();

    while (g_app_status == RUNNING)
    {
        process_input();
        update();
        render();
    }

    shutdown();
    return 0;
}
