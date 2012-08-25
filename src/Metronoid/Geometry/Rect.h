#pragma once
#include "Point.h"
#include "Size.h"
namespace geom
{
	value struct Rect
	{
	internal:
		Rect(Point p, geom::Size s) :
			Position(p),
			Size(s)
		{
		}

		Rect(float x, float y, float width, float height) :
			Position(x, y),
			Size(width, height)
		{
		}

	public:
		Point Position;
		Size Size;
	};
}