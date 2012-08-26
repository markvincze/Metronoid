#include "pch.h"
#include "GameObject.h"
using namespace game;
using namespace geom;

GameObject::GameObject()
{
	LastCollision = 0;
}

void GameObject::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	this->Velocity += this->Acceleration * delta;
	this->Position += this->Velocity * delta;
}

void GameObject::Collide(GameObject^ object)
{
	if(LastCollision > 0.05)
	{
		if(object->Shape == ShapeType::Rectangle)
		{
			if(this->Position.X >= object->Position.X - object->Bounds.Width / 2 - this->Bounds.Width / 2 &&
			   this->Position.X <= object->Position.X + object->Bounds.Width / 2 + this->Bounds.Width / 2 &&
			   this->Position.Y >= object->Position.Y - object->Bounds.Height / 2 - this->Bounds.Height / 2 &&
			   this->Position.Y <= object->Position.Y + object->Bounds.Height / 2 + this->Bounds.Height / 2)
			{
				LastCollision = 0.0;
				Vector newVelocity(Velocity.X * -1 + object->Velocity.X, Velocity.Y + object->Velocity.Y);
				float xDif = (std::min)(abs(this->Position.X - (object->Position.X - object->Bounds.Width / 2)), abs(this->Position.X - (object->Position.X + object->Bounds.Width / 2)));
				float yDif = (std::min)(abs(this->Position.Y - (object->Position.Y - object->Bounds.Height / 2)), abs(this->Position.Y - (object->Position.Y + object->Bounds.Height / 2)));

				if(xDif < yDif)
				{
					Velocity = Vector(Velocity.X * -1 + object->Velocity.X, Velocity.Y + object->Velocity.Y);
				}
				else
				{
					Velocity = Vector(Velocity.X + object->Velocity.X, Velocity.Y * -1 + object->Velocity.Y);;
				}
			}
		}
	}
}
