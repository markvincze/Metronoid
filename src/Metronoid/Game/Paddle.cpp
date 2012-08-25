#include "pch.h"
#include "Paddle.h"
using namespace game;

Paddle::Paddle()
{
}

void Paddle::Step(float delta, geom::Point pointerPosition)
{
	this->Velocity = this->Position.VectorTo(pointerPosition) * 7;

	this->Position += this->Velocity * delta;
}

void Paddle::Render(IMetronoidRenderer^ renderer)
{
	geom::Rect destination(Position.X - 10, Position.Y - 50, 20, 100);

	renderer->FillRectangle(destination, Windows::UI::Colors::Black);
}

void Paddle::Collide(GameObject^ object)
{
}