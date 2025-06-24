#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH        = 800 * 1.5f,
              SCREEN_HEIGHT       = 450 * 1.5f,
              FPS                 = 60,
              NUMBER_OF_PLATFORMS = 3;

constexpr char SAPPHO_FP[]     = "assets/sappho.png";
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

// Global Variables
AppStatus gAppStatus   = RUNNING;
Entity* gPlayer        = nullptr;
Entity* gPlatforms     = nullptr;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

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
        100, 100,
        500,
        SAPPHO_FP 
    };

    gPlayer->setPosition({ 
        gPlayer->getPosition().x, 
        gPlayer->getPosition().y - gPlayer->getHeight()
    });

    gPlatforms = new Entity[NUMBER_OF_PLATFORMS];

    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++)
    {
        gPlatforms[i] = Entity {
            SCREEN_WIDTH, SCREEN_HEIGHT,
            100, 100,
            500,
            SAPPHO_FP 
        };

        gPlatforms[i].setPosition({
            gPlatforms[i].getPosition().x + gPlatforms[i].getWidth()  * (i - 1),
            gPlatforms[i].getPosition().y + gPlatforms[i].getHeight() * 2
        });

        gPlatforms[i].setAcceleration({ 0.0f, 0.0f });
    }

    SetTargetFPS(FPS);
}

void processInput() 
{
    gPlayer->resetMovement();

    if      (IsKeyDown(KEY_A)) gPlayer->moveLeft();
    else if (IsKeyDown(KEY_D)) gPlayer->moveRight();
    if      (IsKeyDown(KEY_W)) gPlayer->moveUp();
    else if (IsKeyDown(KEY_S)) gPlayer->moveDown();

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) 
        gAppStatus = TERMINATED;
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
        gPlayer->update(FIXED_TIMESTEP, gPlatforms, NUMBER_OF_PLATFORMS);

        for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) 
            gPlatforms[i].update(FIXED_TIMESTEP, nullptr, 0);

        deltaTime -= FIXED_TIMESTEP;
    }

    gTimeAccumulator = deltaTime;
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gPlayer->render();
    for (int i = 0; i < NUMBER_OF_PLATFORMS; i++) 
            gPlatforms[i].render();

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