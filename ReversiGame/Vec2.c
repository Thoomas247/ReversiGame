#include "Vec2.h"

Vec2 Vec2_add(Vec2 a, Vec2 b)
{
	Vec2 vec = { a.x + b.x, a.y + b.y };
	return vec;
}

BOOL Vec2_equal(Vec2 a, Vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}

int Vec2_componentSum(Vec2 a)
{
	return a.x + a.y;
}
