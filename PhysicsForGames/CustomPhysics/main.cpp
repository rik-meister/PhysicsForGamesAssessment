#include "DemoWorld.h"

#include <raylib.h>


int main(void)
{
    World* Game = new DemoWorld();

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

    delete Game;

    return 0;
}