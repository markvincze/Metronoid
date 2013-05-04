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
	// Képernyõ tetejébe ütközés.
	if(Position.Y <= Bounds.Height / 2 && Velocity.Y < 0)
	{
		Velocity = geom::Vector(Velocity.X, Velocity.Y * -1);
	}

	// Képernyõ oldalába ütközés.
	if(Position.X <= Bounds.Width / 2 && Velocity.X < 0 || Position.X >= screenSize.Width - Bounds.Width / 2 && Velocity.X > 0)
	{
		Velocity = geom::Vector(Velocity.X * -1, Velocity.Y);
	}

	GameObject::Step(delta, pointerPosition, screenSize);

	if(Velocity.Length > MaxSpeed)
	{
		Velocity *= (MaxSpeed / Velocity.Length);
	}
}

bool Ball::CheckCollision(GameObject^ object)
{
	bool result = GameObject::CheckCollision(object);

	if(result && object->Type == GameObjectType::Paddle)
	{
		// Ha az ütõvel ütközik, akkor módosítjuk az irányát, ha sikerült visszaütni.
		if(Velocity.Y < 0)
		{
			auto length = Velocity.Length;
			auto distanceFromPaddleCenter = Position.X - object->Position.X;
			auto ratio = distanceFromPaddleCenter / object->Bounds.Width;

			Vector temp(ratio, -(1 - abs(ratio)));
			temp = temp.Normalized();
			Velocity = temp * length;
		}
	}

	return result;
}

void Ball::Render(IMetronoidRenderer^ renderer)
{
	renderer->FillEllipse(Position, Bounds.Width / 2, Bounds.Height / 2, FillColor);
}