#pragma once

#include "GameOptions.h"

typedef struct Vec2
{
	int x;
	int y;
} Vec2;

Vec2 Vec2_add(Vec2 a, Vec2 b)
{
	Vec2 vec = { a.x + b.x, a.y + b.y };
	return vec;
}

BOOL Vec2_equal(Vec2 a, Vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}