#include "PhysObject.h"

void PhysObject::TickPhys(float Delta)
{
	
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
