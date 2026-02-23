#pragma once

#include <Vector2Int.h>

struct Rect
{
	Vector2Int point;
	Vector2Int size;

	Rect(const Vector2Int& point, const Vector2Int& size)
		: point(point),
		  size(size)
	{
	}
};