#pragma once
#include "../Geometry/Point.h"
#include "../Geometry/Rect.h"

interface class IMetronoidRenderer
{
public:
	virtual	void FillRectangle(geom::Rect destination, Windows::UI::Color fillColor) = 0;
	virtual void FillEllipse(geom::Point point, float radiusX, float radiusY, Windows::UI::Color fillColor) = 0;
	virtual void DrawText(Platform::String^ text, double fontSize, double x, double y, Windows::UI::Color color) = 0;
	virtual void Clear(Windows::UI::Color fillColor) = 0;
};