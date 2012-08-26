#pragma once
#include "GameObjectType.h"
#include "../Geometry/Point.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Size.h"
#include "../Interfaces/IMetronoidRenderer.h"
namespace game
{
	ref class GameObject
	{
	internal:
		GameObject();

		virtual void Step(float delta, geom::Point pointerPosition, geom::Size screenSize);
		virtual void Collide(GameObject^ object) = 0;
		virtual void Render(IMetronoidRenderer^ renderer) = 0;
		virtual property GameObjectType Type{ GameObjectType get() = 0;}

		property geom::Point Position;
		property geom::Vector Velocity;
		property geom::Vector Acceleration;

		property geom::Size Bounds;

	protected:
		property float LastCollision;
	};
}