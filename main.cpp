#include "CS3113/cs3113.h"

// Global Constants
constexpr int SCREEN_WIDTH  = 800,
              SCREEN_HEIGHT = 450,
              FPS           = 60;

constexpr char SAPPHO_FP[] = "assets/sappho.png";

// Global Variables
AppStatus gAppStatus = RUNNING;
Entity* gPlayer = nullptr;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");
    // hello();

    Rectangle body = {
        SCREEN_WIDTH  / 2.0f,
        SCREEN_HEIGHT / 2.0f,
        SIZE, 
        SIZE
    };

    Vector2 startingPosition = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };

    gPlayer = new Entity(body, startingPosition);

    // gPlayer.body = ;

    // gPlayer.movement = { 0.0f, 0.0f };
    // gPlayer.position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };

    SetTargetFPS(FPS);
}

void processInput() 
{
    gPlayer->mMovement = { 0.0f, 0.0f };

    if      (IsKeyDown(KEY_A)) gPlayer->mMovement.x =  1;
    else if (IsKeyDown(KEY_D)) gPlayer->mMovement.x = -1;
    else if (IsKeyDown(KEY_W)) gPlayer->mMovement.y = -1;
    else if (IsKeyDown(KEY_S)) gPlayer->mMovement.y =  1;

    if (IsKeyDown(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update()
{
    // resetEntity(gPlayer);

    gPlayer->mPosition.x += gPlayer->mMovement.x * 2;
    gPlayer->mPosition.y += gPlayer->mMovement.y * 2;

    // translate(gPlayer);
}

void render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangleRec(gPlayer->mBody, RED);

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