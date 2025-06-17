#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 2,
              SCREEN_HEIGHT = 450 * 2,
              FPS           = 60;

constexpr char SAPPHO_FP[] = "/Users/sebastianromerocruz/Documents/Prōposita/game-dev/raylib/raylib-user-input/assets/sappho.png";

// Global Variables
AppStatus gAppStatus = RUNNING;
Entity* gPlayer = nullptr;
float gTime = 0.0f;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sappho");

    gPlayer = new Entity { 
        SCREEN_WIDTH, SCREEN_HEIGHT,
        10, 10,
        SAPPHO_FP 
    };

    SetTargetFPS(FPS);
}

void processInput() 
{
    gPlayer->resetMovement();

    if      (IsKeyDown(KEY_A)) gPlayer->moveLeft();
    else if (IsKeyDown(KEY_D)) gPlayer->moveRight();
    if      (IsKeyDown(KEY_W)) gPlayer->moveUp();
    else if (IsKeyDown(KEY_S)) gPlayer->moveDown();

    if (IsKeyDown(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    gPlayer->update();
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gPlayer->render();

    EndDrawing();

    gTime += 0.05f;
}

void shutdown() 
{ 
    delete gPlayer;
    CloseWindow(); // Close window and OpenGL context
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    return 0;
}