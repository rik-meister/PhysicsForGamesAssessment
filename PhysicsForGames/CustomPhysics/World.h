#pragma once

#include <vector> // dnamic array (i.e., a TArray)
#include <memory> // for smart pointers
// public - protected - private
// variables first, followed by functions

class PhysObject;

class World
{
public:
	float TargetFixedStep = 1.0f / 30.0f;
	float GravityY = 9.81f;

private:
	float AccumulatedFixedTime = 0.0f;

	std::vector<std::shared_ptr<PhysObject>> PhysObjects;

public:
	void Init();
	void Tick();
	void TickFixed();
	void Draw();
	void Exit();

	// @brief Indicates the game is trying to shut down
	// @return True if shutdown is requested

	bool ShouldClose() const;

	// @brief Indicates the game is due for running TickFixed()
	// @return True if we should call TickFixed() in next update-draw loop, otherwise false
	bool ShouldTickFixed() const;

	std::weak_ptr<PhysObject> SpawnPhysObject();
	void DestroyPhysObject(PhysObject* Target);
	// PhysObject* SpawnPhysObjectUnsafe();

	const std::vector<std::shared_ptr<PhysObject>>& GetPhysObjects() { return PhysObjects; }

protected:

	// Lifecycle Callbacks
	void virtual OnInit() {}
	void virtual OnTick() {}
	void virtual OnTickFixed() {}
	void virtual OnDraw() {}
	void virtual OnExit() {}

private:
};