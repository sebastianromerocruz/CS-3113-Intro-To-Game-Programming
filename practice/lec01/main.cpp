#include "raylib.h"

enum AppStatus { TERMINATED, RUNNING };

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int FPS = 60;

AppStatus gAppStatus = RUNNING;

void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello, Raylib!");
    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() {
    // TODO: take in input
    // TODO: update/calculate game state
    // TODO: render
}

void render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
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