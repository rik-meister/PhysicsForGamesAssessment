#include <memory>

#include <raylib.h>

#include "DemoWorld.h"
#include "Shapes.h"

int main(void)
{

    // only used here
    // will destroy object when ptr falls out of scope
    std::unique_ptr<World> Game = std::make_unique<DemoWorld>();

    Game->Init();

    // Main game loop
    while (!Game->ShouldClose())    // Detect window close button or ESC key
    {
        Game->Tick();
        
        while (Game->ShouldTickFixed())
        {
            Game->TickFixed();
        }

        Game->Draw();
    }

    Game->Exit();

    // manually destroys the underlying object
    // Game.release();

    return 0;
}