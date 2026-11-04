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

	Color DrawColor = bWasHitThisFrame ? RED : GRAY;

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

float ResolveCollision(const Vector2& VelA, float MassA, const Vector2& VelB, float MassB, float Elasticity, const Vector2& Normal)
{
	// calculate relative velocity
	Vector2 RelativeVel = VelA - VelB;

	// calculate impulse magnitude
	float ImpulseMag = Vector2DotProduct(-(1.f + Elasticity) * RelativeVel, Normal) /
		Vector2DotProduct(Normal, Normal * (1.f / MassA + 1.f / MassB));

	// return how strong these things should fly off
	return ImpulseMag;
}

void ResolvePhysBodies(PhysObject& Lhs, PhysObject& Rhs, float Elasticity, const Vector2& Normal, float Pen)
{
	// do nothing if Pen is too small
	if (Pen < 0.001f) { return; }

	// Depenetrate colliding objects
	
	// halve it to apply half of the MTV to each object involved
	Pen /= 2.0f;

	// ensure they seperate enough
	Pen += 0.05f;

	Vector2 LhsNewPosition = Lhs.GetPosition() + Normal * Pen;
	Vector2 RhsNewPosition = Rhs.GetPosition() - Normal * Pen;

	Lhs.SetPosition(LhsNewPosition);
	Rhs.SetPosition(RhsNewPosition);
	
	// Calculate and apply resolution impulse
	float ImpulseMag = ResolveCollision(Lhs.GetVelocity(), Lhs.GetMass(), Rhs.GetVelocity(), Rhs.GetMass(), Elasticity, Normal);

	Vector2 Impulse = ImpulseMag * Normal;
	Lhs.AddImpulse(Impulse);
	Rhs.AddImpulse(Impulse * -1.f);
}
