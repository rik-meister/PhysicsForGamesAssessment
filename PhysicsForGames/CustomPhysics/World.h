#pragma once

// public - protected - private
// variables first, followed by functions

class World
{
public:
	float TargetFixedStep = 1.0f / 30.0f;

private:
	float AccumulatedFixedTime = 0.0f;

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

protected:

	// Lifecycle Callbacks
	void virtual OnInit() {}
	void virtual OnTick() {}
	void virtual OnTickFixed() {}
	void virtual OnDraw() {}
	void virtual OnExit() {}

private:
};