#include "pch.h"
#include "Paddle.h"
using namespace game;
using namespace geom;

Paddle::Paddle() :
	GameObject()
{
	Bounds = Size(20, 100);

	Windows::UI::Color fillColor;

	fillColor.A = 255;
	fillColor.R = 0x01;
	fillColor.G = 0x4C;
	fillColor.B = 0x65;

	FillColor = fillColor;
}

void Paddle::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	this->Velocity = this->Position.VectorTo(pointerPosition) * 7;
	this->Velocity = geom::Vector(0, Velocity.Y);

	this->Position += this->Velocity * delta;
}

void Paddle::Render(IMetronoidRenderer^ renderer)
{
	geom::Rect destination(Position.X - Bounds.Width / 2, Position.Y - Bounds.Height / 2, Bounds.Width, Bounds.Height);

	renderer->FillRectangle(destination, FillColor);
}