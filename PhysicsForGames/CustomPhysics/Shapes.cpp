#include "Shapes.h"

#include <raymath.h>

bool CheckCircleCircle(const Vector2& PosA, const Circle& CircleA, const Vector2& PosB, const Circle& CircleB)
{
    // distance between circles
    float Dist = Vector2Length(PosA - PosB);

    // sum of the radii
    float RadiiSum = CircleA.Radius + CircleB.Radius;

    // return true if overlapping
    // return true if distance is less than sum of the radii
    return Dist <= RadiiSum;
}

bool CheckCircleCircle(const Vector2& PosA, const Shape& CircleA, const Vector2& PosB, const Shape& CircleB)
{
    return CheckCircleCircle(PosA, CircleA.CircleData, PosB, CircleB.CircleData);
}
