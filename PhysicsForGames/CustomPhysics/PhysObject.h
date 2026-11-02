#pragma once

#include <raymath.h>

class PhysObject
{
private:
	Vector2 Position;
	Vector2 Velocity;
public:
	void TickPhys(float Delta);

	void SetPosition(const Vector2& NewPosition);
	Vector2 GetPosition() const;

	void SetVelocity(const Vector2& NewVelocity);
	Vector2 GetVelocity() const;
};