#include "DemoWorld.h"

#include <iostream>

void DemoWorld::OnTick()
{
	World::OnTick();

	std::cout << "Tick" << std::endl;
}

void DemoWorld::OnTickFixed()
{
	World::OnTickFixed();

	std::cout << "TickFixed" << std::endl;
}