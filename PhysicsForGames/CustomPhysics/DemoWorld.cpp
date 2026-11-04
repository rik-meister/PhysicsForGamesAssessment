#include "DemoWorld.h"

#include "PhysObject.h"

#include <iostream>

void DemoWorld::OnInit()
{
	World::OnInit();

	TestPhysObject = SpawnPhysObject();
	if (auto TestPhysObjectReal = TestPhysObject.lock())
	{
		TestPhysObjectReal->SetPosition({ 250, 250 });
		//TestPhysObjectReal->AddVelocityChange({ 100,0 });
		TestPhysObjectReal->SetMass(.1f);
		TestPhysObjectReal->AddImpulse({ 10, 0 });
		//TestPhysObjectReal->SetVelocity({ 50, 0 });

		TestPhysObjectReal->SetCircle(15.0f);
	}

	if (auto AnotherObjectReal = SpawnPhysObject().lock())
	{
		AnotherObjectReal->SetPosition({ 270, 250 });
		AnotherObjectReal->SetCircle(15.0f);
		AnotherObjectReal->AddImpulse({ 15, 0 });
	}

	GravityY = 0.0f; // turn off gravity while we're testing this shizz
}

void DemoWorld::OnTick()
{
	World::OnTick();

	// std::cout << "Tick" << std::endl;
}

void DemoWorld::OnTickFixed()
{
	World::OnTickFixed();

	if (auto TestPhysObjectReal = TestPhysObject.lock())
	{
		// TestPhysObjectReal->AddForce({ -50, 0.0f });
	}

	/*if (bUseScreenWrap)
	{
		for (auto PObj : GetPhysObjects())
		{
			Vector2 NewPosition = PObj->GetPosition();
			NewPosition.x = Wrap(NewPosition.x, GetScreenWidth());
			NewPosition.y = Wrap(NewPosition.y, GetScreenHeight());
			PObj->SetPosition(NewPosition);
		}
	}*/

	// std::cout << "TickFixed" << std::endl;
}