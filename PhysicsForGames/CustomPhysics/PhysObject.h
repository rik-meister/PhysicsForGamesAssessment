#pragma once

#include <raylib.h>		// must come before raymath and placed in header
#include <raymath.h>

#include "Shapes.h"

class PhysObject
{
private:
	Vector2 Position;
	Vector2 Velocity;

	float Mass = 1.0f;
	
	Shape Collider;

	Vector2 PendingForces = {};
	Vector2 PendingImpulses = {};

public:
	void TickPhys(float Delta);

	void Draw();

	void SetPosition(const Vector2& NewPosition);
	Vector2 GetPosition() const;

	void SetVelocity(const Vector2& NewVelocity);
	Vector2 GetVelocity() const;

	void SetMass(float NewMass);
	float GetMass() const { return Mass; }

	void SetCircle(float Radius);
	const Shape& GetShape() const;

	void AddForce(const Vector2& Force);
	void AddAccel(const Vector2& Accel);
	void AddImpulse(const Vector2& Impulse);
	void AddVelocityChange(const Vector2& VelChange);
};