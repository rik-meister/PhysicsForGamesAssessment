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

// Function pointer to a shape-shape Depenetration function
using DepenetrationFunc = Vector2(*) (const Vector2&, const Shape&, const Vector2&, const Shape&, float&);

// Lookup table for pairs of Shapes (and get its Depenetration func back)
using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;

// static linkage (i.e., only available here)

// lookup map for collision detection functions
CollisionMap CollisionCheckers;

// lookup map for depenetration functions
DepenetrationMap CollisionDepenetrators;

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
    CollisionDepenetrators[ShapeType::CIRCLE | ShapeType::CIRCLE] = DepenetrateCircleCircle;

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
                Lhs->NotifyHit(Lhs->GetShape(), Rhs.get(), Rhs->GetShape(), {}, {}, {});

                float Pen = 0.0f;
                Vector2 Dir = CollisionDepenetrators[PairType](Lhs->GetPosition(), Lhs->GetShape(), Rhs->GetPosition(), Rhs->GetShape(), Pen);

                ResolvePhysBodies(*Lhs.get(), *Rhs.get(), 0.1f, Dir, Pen);

                //std::cout << "omg collision" << std::endl;
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

void World::DestroyPhysObject(PhysObject* Target)
{
    // early exit if invalid
    if (Target == nullptr) { return; }

    PhysObjects.erase(std::remove_if(PhysObjects.begin(), PhysObjects.end(), [Target](const auto& Ptr) {
        return Ptr.get() == Target;
        }), PhysObjects.end());
}

