// include the header we are implementing
#include "World.h"

// compiler headers
#include <iostream>
#include <unordered_map>

// third party dependencies
#include <raylib.h>

// project
#include "EnumUtils.h"
#include "PhysObject.h"

// function pointers

// function pointer to a shape-shape collision detection function
using CollisionFunc = bool (*) (const Vector2&, const Shape&, const Vector2&, const Shape&);

// Lookup table for pairs of Shapes (and get its collision detection func back)
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;

// static linkage (i.e., only available here)

// lookup map for collision detection functions
CollisionMap CollisionCheckers;

void World::Init()
{
    // Initialization
//--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Setup my collision detection functions
    //---------------------------------------
    CollisionCheckers[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;

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

    // integrate forces and velocity
    for (auto const PObj : PhysObjects)
    {
        PObj->AddAccel({ 0.0f, GravityY });
        PObj->TickPhys(TargetFixedStep);
    }

    // check for collisions
    for (auto PObjA : PhysObjects)
    {
        for (auto PObjB : PhysObjects)
        {
            // skip self collision
            if (PObjA == PObjB) { continue; }
            // skip if an object lacks a collider
            if (PObjA->GetShape().Type == ShapeType::NONE || 
                PObjB->GetShape().Type == ShapeType::NONE) { continue; }

            // reorder my pointers so the lower type always first
            std::shared_ptr<PhysObject> Lhs = PObjA;
            std::shared_ptr<PhysObject> Rhs = PObjB;

            // HACK: check the type and swaap if necessary
            if (PObjA->GetShape().Type > PObjB->GetShape().Type)
            {
                Lhs = PObjB;
                Rhs = PObjA;
            }

            ShapeType PairType = Lhs->GetShape().Type | Rhs->GetShape().Type;
            bool bIsColliding = CollisionCheckers[PairType](Lhs->GetPosition(), Lhs->GetShape(), Rhs->GetPosition(), Rhs->GetShape());

            if (bIsColliding)
            {
                std::cout << "omg collision" << std::endl;
            }
        }
    }

    OnTickFixed();
}

void World::Draw()
{
    // Draw stuff during rendering
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Bing Bong", 350, 200, 20, LIGHTGRAY);

    for (auto const PObj : PhysObjects)
    {
        PObj->Draw();
    }

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

std::weak_ptr<PhysObject> World::SpawnPhysObject()
{
    PhysObjects.emplace_back(std::make_shared<PhysObject>());

    return PhysObjects[PhysObjects.size() - 1];
}


