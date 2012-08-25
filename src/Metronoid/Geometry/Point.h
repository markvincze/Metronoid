#pragma once
#include "Vector.h"

namespace geom
{
	value struct Point
	{
	internal:

		Point(float x, float y) :
			X(x),
			Y(y)
		{
		}

		Vector VectorTo(const Point& to)
		{
			return Vector(to.X - X, to.Y - Y);
		}

		Point operator+(const Point& other)
		{
			return Point(X + other.X, Y + other.Y);
		}

		Point operator-(const Point& other)
		{
			return Point(X - other.X, Y - other.Y);
		}

		Point operator+(const Vector& v)
		{
			return Point(X + v.X, Y + v.Y);
		}

		Point operator-(const Vector& v)
		{
			return Point(X - v.X, Y - v.Y);
		}
	public:
		float X;
		float Y;
	};
}