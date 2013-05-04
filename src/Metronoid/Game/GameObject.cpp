#include "pch.h"
#include "GameObject.h"
using namespace game;
using namespace geom;

GameObject::GameObject()
{
	LastCollision = 0;
	JustCollided = false;
}

void GameObject::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	this->Velocity += this->Acceleration * delta;
	this->Position += this->Velocity * delta;
}

bool GameObject::CheckCollision(GameObject^ object)
{
	if(Shape == ShapeType::Ellipse)
	{
		if(object->Shape == ShapeType::Rectangle)
		{
			float circleDistanceX = abs(Position.X - object->Position.X);
			float circleDistanceY = abs(Position.Y - object->Position.Y);

			float objectBoundsWidthHalf = object->Bounds.Width / 2;
			float objectBoundsHeightHalf = object->Bounds.Height / 2;
			float boundsWidthHalf = this->Bounds.Width / 2;
			float boundsHeightHalf = this->Bounds.Height / 2;

			if (circleDistanceX > (objectBoundsWidthHalf + boundsWidthHalf) ||
				(circleDistanceY > (objectBoundsHeightHalf + boundsHeightHalf)))
			{
				if(LastCollidedWith == object)
				{
					// Elt�volodtunk az objektumt�l, akivel legut�bb �tk�zt�nk.
					JustCollided = false;
				}

				return false;
			}

			if(!JustCollided)
			{
				if (circleDistanceX <= (objectBoundsWidthHalf))
				{
					Velocity = Vector(Velocity.X + object->Velocity.X * 0.2, Velocity.Y * -1 + object->Velocity.Y * 0.2);
					if(object->Type == GameObjectType::Paddle)
					{
						LastCollidedWith = object;
						JustCollided = true;
					}
					return true;
				}

				if (circleDistanceY <= (objectBoundsHeightHalf))
				{
					Velocity = Vector(Velocity.X * -1 + object->Velocity.X * 0.2, Velocity.Y + object->Velocity.Y * 0.2);
					if(object->Type == GameObjectType::Paddle)
					{
						LastCollidedWith = object;
						JustCollided = true;
					}
					return true;
				}

				float cornerDistanceSq = pow(circleDistanceX - objectBoundsWidthHalf, 2) +
					pow(circleDistanceY - objectBoundsHeightHalf, 2);

				if(cornerDistanceSq <= pow(boundsWidthHalf, 2))
				{
					Vector temp = Position - object->Position;
					Vector normal = (Position - Point(
						object->Position.X + sgn(temp.X) * objectBoundsWidthHalf,
						object->Position.Y + sgn(temp.Y) * objectBoundsHeightHalf)).Normalized();

					Velocity = Velocity - (normal * (2 * (Velocity * normal)));

					if(object->Type == GameObjectType::Paddle)
					{
						LastCollidedWith = object;
						JustCollided = true;
					}

					// HACK: A labda ne mehessen nagyon �les sz�gben felfel� vagy lefel�.
					if(Type == GameObjectType::Ball)
					{
						if(abs(Velocity.X) < abs(Velocity.Y))
						{
							auto multiplier = Velocity.Length / sqrt(2);
							Velocity = Vector(sgn(Velocity.X) * multiplier, sgn(Velocity.Y) * multiplier);
						}
					}

					return true;
				}
			}

			if(LastCollidedWith == object)
			{
				// Elt�volodtunk az objektumt�l, akivel legut�bb �tk�zt�nk.
				JustCollided = false;
			}

			return false;
		}
	}

	return false;
}

void GameObject::ApplyCollisionEffect(GameObject^ object)
{
}
