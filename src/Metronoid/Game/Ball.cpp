#include "pch.h"
#include "Ball.h"
#include "Paddle.h"
#include <algorithm>
#include <cmath>
using namespace game;
using namespace geom;

Ball::Ball(void) :
	GameObject()
{
	Bounds = Size(20, 20);

	MaxSpeed = 500;

	Windows::UI::Color fillColor;

	fillColor.A = 255;
	fillColor.R = 0x01;
	fillColor.G = 0x4C;
	fillColor.B = 0x65;

	FillColor = fillColor;
}

void Ball::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	if(Position.Y <= Bounds.Height / 2 && Velocity.Y < 0 || Position.Y >= screenSize.Height - Bounds.Height / 2 && Velocity.Y > 0)
	{
		Velocity = geom::Vector(Velocity.X, Velocity.Y * -1);
	}

	if(/*Position.X <= Bounds.Width / 2 && Velocity.X < 0 || */Position.X >= screenSize.Width - Bounds.Width / 2 && Velocity.X > 0)
	{
		Velocity = geom::Vector(Velocity.X * -1, Velocity.Y);
	}

	GameObject::Step(delta, pointerPosition, screenSize);

	if(Velocity.Length > MaxSpeed)
	{
		Velocity *= (MaxSpeed / Velocity.Length);
	}
}

void Ball::Render(IMetronoidRenderer^ renderer)
{
	renderer->FillEllipse(Position, Bounds.Width / 2, Bounds.Height / 2, FillColor);
}