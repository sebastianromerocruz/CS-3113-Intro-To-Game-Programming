#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 2,
              SCREEN_HEIGHT = 450 * 2,
              FPS           = 60;

constexpr char SAPPHO_FP[] = "/Users/sebastianromerocruz/Documents/Prōposita/game-dev/raylib/raylib-user-input/assets/sappho.png";
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus = RUNNING;
Entity* gPlayer = nullptr;
float gPreviousTicks = 0.0f;
float gTimeAccumulator = 0.0f;
int gAccTimes = 0;

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

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    // Delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    // Fixed timestep
    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    gAccTimes = 0;

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gPlayer->update(deltaTime);
        deltaTime -= FIXED_TIMESTEP;
    }

    gTimeAccumulator = deltaTime;
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gPlayer->render();

    EndDrawing();
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