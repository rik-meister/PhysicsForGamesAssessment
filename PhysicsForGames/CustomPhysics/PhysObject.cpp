#include "PhysObject.h"

#include <cassert>		//assert
#include <raymath.h>

void PhysObject::TickPhys(float Delta)
{
	// integrate impulses into velocity
	Velocity += PendingImpulses;
	PendingImpulses = {}; // zeros out after integration

	// integrate forces into velocity
	Velocity += PendingForces * Delta;
	PendingForces = {}; // zeros out after integration

	// integrate velocity into pos
	Position += Velocity * Delta;
}

void PhysObject::Draw()
{
	Vector2 XRay = Position + Vector2{ 50, 0 };
	Vector2 YRay = Position + Vector2{ 0, 50 };

	DrawLineV(Position, XRay, RED);
	DrawLineV(Position, YRay, GREEN);

	switch (Collider.Type)
	{
	case ShapeType::NONE:
		DrawPixelV(Position, RED);
		break;

	case ShapeType::CIRCLE:
		DrawCircleLinesV(Position, Collider.CircleData.Radius, RED);
		break;

	default:
		//include <cassert> for this
		assert(false && "Bad Enum!! This Should never happen!!");
	}
}

void PhysObject::SetPosition(const Vector2& NewPosition)
{
	Position = NewPosition;
}

Vector2 PhysObject::GetPosition() const
{
	return Position;
}

void PhysObject::SetVelocity(const Vector2& NewVelocity)
{
	Velocity = NewVelocity;
}

Vector2 PhysObject::GetVelocity() const
{
	return Velocity;
}

void PhysObject::SetMass(float NewMass)
{
	Mass = NewMass;
}

void PhysObject::SetCircle(float Radius)
{
	Collider.Type = ShapeType::CIRCLE;
	Collider.CircleData.Radius = Radius;
}

const Shape& PhysObject::GetShape() const
{
	return Collider;
}

void PhysObject::AddForce(const Vector2& Force)
{
	PendingForces += Force / Mass;
}

void PhysObject::AddAccel(const Vector2& Accel)
{
	PendingForces += Accel;
}

void PhysObject::AddImpulse(const Vector2& Impulse)
{
	PendingImpulses += Impulse / Mass;
}

void PhysObject::AddVelocityChange(const Vector2& VelChange)
{
	PendingImpulses += VelChange;
}
