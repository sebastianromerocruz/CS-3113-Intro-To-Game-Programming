#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 800 * 1.5f,
              SCREEN_HEIGHT = 450 * 1.5f,
              FPS           = 60;

constexpr char SAPPHO_FP[] = "/Users/sebastianromerocruz/Documents/Prōposita/game-dev/raylib/raylib-user-input/assets/sappho.png";
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus = RUNNING;
Entity* gEntityA = nullptr;
Entity* gEntityB = nullptr;
float gPreviousTicks = 0.0f;
float gTimeAccumulator = 0.0f;

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

    gEntityA = new Entity { 
        SCREEN_WIDTH, SCREEN_HEIGHT,
        100, 100,
        500,
        SAPPHO_FP 
    };

    gEntityB = new Entity { 
        SCREEN_WIDTH, SCREEN_HEIGHT,
        100, 100,
        500,
        SAPPHO_FP 
    };

    gEntityB->setPosition({gEntityB->getPosition().x + 200, gEntityB->getPosition().y + 200});

    SetTargetFPS(FPS);
}

void processInput() 
{
    gEntityA->resetMovement();

    if      (IsKeyDown(KEY_A)) gEntityA->moveLeft();
    else if (IsKeyDown(KEY_D)) gEntityA->moveRight();
    if      (IsKeyDown(KEY_W)) gEntityA->moveUp();
    else if (IsKeyDown(KEY_S)) gEntityA->moveDown();

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

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gEntityA->update(FIXED_TIMESTEP);
        gEntityB->update(FIXED_TIMESTEP);

        // if (gEntityA->checkCollision(gEntityB)) printf("Collision\n");

        deltaTime -= FIXED_TIMESTEP;
    }

    gTimeAccumulator = deltaTime;
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gEntityA->render();
    gEntityB->render();

    EndDrawing();
}

void shutdown() 
{ 
    delete gEntityA;
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