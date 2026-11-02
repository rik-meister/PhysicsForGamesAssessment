// include the header we are implementing
#include "World.h"


// third party dependencies
#include <raylib.h>

void World::Init()
{
    // Initialization
//--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Do initialization stuff after raylib
    OnInit();
}

void World::Tick()
{
    // Incrementing the fixed tick timer
    AccumulatedFixedTime += GetFrameTime();
    // NOTE: Raylib 6.0 + vcpkg does NOT implement GetFrameTime() correctly

    // Call tick
    OnTick();
}

void World::TickFixed()
{
    AccumulatedFixedTime -= TargetFixedStep;

    OnTickFixed();
}

void World::Draw()
{
    // Draw stuff during rendering
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    OnDraw();

    EndDrawing();
}


void World::Exit()
{
    // Exit BEFORE raylib exists
    OnExit();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

bool World::ShouldClose() const
{
    return WindowShouldClose();
}

bool World::ShouldTickFixed() const
{
    return AccumulatedFixedTime >= TargetFixedStep;
}