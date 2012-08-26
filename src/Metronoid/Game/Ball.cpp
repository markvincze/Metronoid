#include "pch.h"
#include "Ball.h"
#include "Paddle.h"
using namespace game;
using namespace geom;

Ball::Ball(void) :
	GameObject()
{
	Bounds = Size(10, 10);
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
	renderer->FillEllipse(Position, Bounds.Width, Bounds.Height, Windows::UI::Colors::Black);
}

void Ball::Collide(GameObject^ object)
{
	if(LastCollision > 0.05)
	{
		if(object->Type == GameObjectType::Paddle)
		{
			Paddle^ paddle = dynamic_cast<Paddle^>(object);

			if(Position.X <= paddle->Position.X + paddle->Bounds.Width / 2
				&& Position.Y >= paddle->Position.Y - paddle->Bounds.Height / 2
				&& Position.Y <= paddle->Position.Y + paddle->Bounds.Height / 2)
			{
				LastCollision = 0.0;
				Velocity = geom::Vector(Velocity.X * -1, Velocity.Y + paddle->Velocity.Y);
			}
		}
	}
}