#include "pch.h"
#include "Paddle.h"
using namespace game;
using namespace geom;

Paddle::Paddle() :
	GameObject()
{
	Bounds = Size(20, 100);
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

	renderer->FillRectangle(destination, Windows::UI::Colors::Black);
}

void Paddle::Collide(GameObject^ object)
{
}