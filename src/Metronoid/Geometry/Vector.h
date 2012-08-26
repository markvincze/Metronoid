#pragma once
#include <cmath>
namespace geom
{
	value struct Vector
	{
	internal:
		Vector(float x, float y) :
			X(x),
			Y(y)
		{
		}

		Vector operator+(const Vector& other)
		{
			return Vector(X + other.X, Y + other.Y);
		}

		Vector operator-(const Vector& other)
		{
			return Vector(X - other.X, Y - other.Y);
		}

		Vector operator*(const float& r)
		{
			return Vector(r * X, r * Y);
		}

		float operator*(const Vector& other)
		{
			return X * other.X + Y * other.Y;
		}

		property float Length
		{
			float get()
			{
				return std::sqrt(X * X + Y * Y);
			}
		}

		Vector Normalized()
		{
			float length = Length;
			return Vector(X / length, Y / length);
		}
		//property Vector Normal
		//{
		//	Vector get()
		//	{
		//		float length = std::sqrt(X * X + Y * Y);
		//		//return Vector(X / length, Y / length);
		//		return Vector(0, 0);
		//	}
		//}

	public:
		float X;
		float Y;
	};
}