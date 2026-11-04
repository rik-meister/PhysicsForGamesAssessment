#include "DemoWorld.h"

#include "PhysObject.h"

#include <cmath>
#include <iostream>

float Wrap(float Val, float Limit)
{
	return std::fmod(std::fmod(Val, Limit) + Limit, Limit);
}

void DemoWorld::OnInit()
{
	World::OnInit();

	TestPhysObject = SpawnPhysObject();
	if (auto TestPhysObjectReal = TestPhysObject.lock())
	{
		TestPhysObjectReal->SetPosition({ 50, 100 });
		//TestPhysObjectReal->AddVelocityChange({ 100,0 });
		TestPhysObjectReal->SetMass(1.0f);
		TestPhysObjectReal->AddImpulse({ 150, 0 });
		//TestPhysObjectReal->SetVelocity({ 50, 0 });

		TestPhysObjectReal->SetCircle(50.0f);
	}

	if (auto AnotherObjectReal = SpawnPhysObject().lock())
	{
		AnotherObjectReal->SetPosition({ 700, 100 });
		AnotherObjectReal->SetCircle(50.0f);
		AnotherObjectReal->AddImpulse({ -155, 0 });
	}

	GravityY = 0.0f; // turn off gravity while we're testing this shizz
}

void DemoWorld::OnTick()
{
	World::OnTick();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (auto TestPhysObjectReal = TestPhysObject.lock())
		{
			TestPhysObjectReal->SetPosition(GetMousePosition());
		}
	}
	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		if (auto NewPhysObjectReal = SpawnPhysObject().lock())
		{
			NewPhysObjectReal->SetPosition(GetMousePosition());
			NewPhysObjectReal->SetCircle(GetRandomValue(15, 30));
		}
	}
	/*else if (IsKeyPressed(KEY_BACKSPACE))
	{
		auto Hits = OverlapCircle(GetMousePosition(), 100.0f);
		for (auto HitObject : Hits)
		{
			DestroyPhysObject(HitObject.lock().get());
		}
	}*/

	// std::cout << "Tick" << std::endl;
}

void DemoWorld::OnTickFixed()
{
	World::OnTickFixed();

	if (auto TestPhysObjectReal = TestPhysObject.lock())
	{
		// TestPhysObjectReal->AddForce({ -50, 0.0f });
	}

	if (bUseScreenWrap)
	{
		for (auto PObj : GetPhysObjects())
		{
			Vector2 NewPosition = PObj->GetPosition();
			NewPosition.x = Wrap(NewPosition.x, GetScreenWidth());
			NewPosition.y = Wrap(NewPosition.y, GetScreenHeight());
			PObj->SetPosition(NewPosition);
		}
	}

	// std::cout << "TickFixed" << std::endl;
}