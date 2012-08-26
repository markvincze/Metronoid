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
	Bounds = Size(10, 10);

	Windows::UI::Color fillColor;

	fillColor.A = 255;
	fillColor.R = 0x01;
	fillColor.G = 0x4C;
	fillColor.B = 0x65;

	FillColor = fillColor;
}

void Ball::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	LastCollision += delta;
	if(LastCollision > 0.05)
	{
		if(Position.Y <= Bounds.Height / 2 || Position.Y >= screenSize.Height - Bounds.Height / 2)
		{
			LastCollision = 0.0;
			Velocity = geom::Vector(Velocity.X, Velocity.Y * -1);
		}

		if(Position.X >= screenSize.Width - Bounds.Width / 2)
		{
			LastCollision = 0.0;
			Velocity = geom::Vector(Velocity.X * -1, Velocity.Y);
		}
	}

	GameObject::Step(delta, pointerPosition, screenSize);
}

void Ball::Render(IMetronoidRenderer^ renderer)
{
	renderer->FillEllipse(Position, Bounds.Width, Bounds.Height, FillColor);
}