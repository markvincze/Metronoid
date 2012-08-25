#pragma once
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
	public:
		float X;
		float Y;
	};
}