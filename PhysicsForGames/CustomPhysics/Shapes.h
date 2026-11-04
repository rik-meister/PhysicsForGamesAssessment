#pragma once

#include <cstdint>

#include <raylib.h>

struct Circle
{
	float Radius;
};

struct AABB
{
	Vector2 HalfExtents;
};

enum class ShapeType : uint8_t
{
	NONE	= 0,
	CIRCLE	= 1 << 0,
	AABB	= 1 << 1
};

struct Shape
{
	ShapeType Type = ShapeType::NONE;
	union
	{
		Circle CircleData;
		AABB AABBData;
	};
};

bool CheckCircleCircle(const Vector2& PosA, const Circle& CircleA, const Vector2& PosB, const Circle& CircleB);
bool CheckCircleCircle(const Vector2& PosA, const Shape& CircleA, const Vector2& PosB, const Shape& CircleB);

Vector2 DepenetrateCircleCircle(const Vector2& PosA, const Circle& CircleA, const Vector2& PosB, const Circle& CircleB, float& Pen);
Vector2 DepenetrateCircleCircle(const Vector2& PosA, const Shape& CircleA, const Vector2& PosB, const Shape& CircleB, float& Pen);
