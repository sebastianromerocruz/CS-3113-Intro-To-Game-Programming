#include "raylib.h"

enum AppStatus { TERMINATED, RUNNING };
enum AngleDirection { LEFT = -1, RIGHT = 1 };
enum ScaleDirection { SMALLER = -1, BIGGER = 1 };
enum XDirection { moveLEFT = -1, moveRIGHT = 1 };
enum YDirection { moveUP = -1, moveDOWN = 1 };


constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 60;
constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
constexpr int RADIUS = 100,
              SIDES = 3;

constexpr float ANGLE_LIMIT_BOTH = 30.0f;
constexpr float MAXIMUM_SCALE = 2.0f;
constexpr float MINIMUM_SCALE = 0.5f;

AppStatus gAppStatus = RUNNING;
float gAngle = 0.0f;
float gScale = 1.0f;
AngleDirection gAngleDirection = RIGHT;
ScaleDirection gScaleDirection = BIGGER;
XDirection gXDirection = moveRIGHT;
YDirection gYDirection = moveDOWN;

Color gColor = RED;
Color colorFromVector(int x, int y, int z) {
    while (x > 255) x -= 255;
    while (y > 255) y -= 255;
    while (z > 255) z -= 255;
    while (x < 0) x += 255;
    while (y < 0) y += 255;
    while (z < 0) z += 255;
    return (Color){
        (unsigned char)x,
        (unsigned char)y,
        (unsigned char)z,
        255
    };
}
int gcolorX = 0;
int gcolorY = 0;
int gcolorZ = 0;

float xPositionOffset = 0;
float yPositionOffset = 0;

Vector2 ApplyOffset(Vector2 position, float xOffset, float yOffset) {
    return (Vector2){
        position.x + xPositionOffset,
        position.y + yPositionOffset
    };
}

void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, Raylib!");
    SetTargetFPS(FPS);
    // ClearBackground(WHITE);
}

void processInput() {
    if (WindowShouldClose()) gAppStatus = TERMINATED;
    if (IsKeyPressed(KEY_ESCAPE)) gAppStatus = TERMINATED;
    if (IsKeyDown(KEY_LEFT_SUPER) && IsKeyPressed(KEY_W)) gAppStatus = TERMINATED;
}

void update() {
    gAngle += .1f * gAngleDirection;
    if (gAngle >= ANGLE_LIMIT_BOTH) gAngleDirection = LEFT;
    else if (gAngle <= -ANGLE_LIMIT_BOTH) gAngleDirection = RIGHT;
    gcolorX += 1;
    gcolorY += 2;
    gcolorZ += 3;
    gColor = colorFromVector(gcolorX, gcolorY, gcolorZ);
    gScale += .01f * gScaleDirection;
    if (gScale >= MAXIMUM_SCALE) gScaleDirection = SMALLER;
    else if (gScale <= MINIMUM_SCALE) gScaleDirection = BIGGER;
    xPositionOffset += 0.1f * gXDirection;
    yPositionOffset += 0.2f * gYDirection;
    if (xPositionOffset >= SCREEN_WIDTH / 2) gXDirection = moveLEFT;
    else if (xPositionOffset <= -SCREEN_WIDTH / 2) gXDirection = moveRIGHT;
    if (yPositionOffset >= SCREEN_HEIGHT / 2) gYDirection = moveUP;
    else if (yPositionOffset <= -SCREEN_HEIGHT / 2) gYDirection = moveDOWN;
}

void render() {
    BeginDrawing();
    ClearBackground(colorFromVector(255 - gcolorX, 255 - gcolorY, 255 - gcolorZ));

    DrawPoly(
        ApplyOffset(ORIGIN, xPositionOffset, yPositionOffset),
        SIDES,
        RADIUS * gScale,
        gAngle,
        gColor
    );

    EndDrawing();
}

void shutdown() {
    CloseWindow();
}

int main(void) {
    initialise();

    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}