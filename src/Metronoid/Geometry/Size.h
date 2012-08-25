#pragma once
namespace geom
{
	value struct Size
	{
	internal:
		Size(float width, float height)
			: Width(width), Height(height)
		{
		};
		
		Size operator +(const Size &other)
		{
			return Size(Width + other.Width, Height + other.Height);
		}

		Size operator -(const Size &other)
		{
			return Size(Width - other.Width, Height - other.Height);
		}
	public:
		float Width, Height;
	};
}