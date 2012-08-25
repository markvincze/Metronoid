#pragma once
#include "../Geometry/Point.h"
#include "../Geometry/Vector.h"
#include "../Interfaces/IMetronoidRenderer.h"
namespace game
{
	ref class GameObject
	{
	internal:
		GameObject();

		virtual void Step(float delta, geom::Point pointerPosition);
		virtual void Collide(GameObject^ object) = 0;
		virtual void Render(IMetronoidRenderer^ renderer) = 0;

		property geom::Point Position;
		property geom::Vector Velocity;
		property geom::Vector Acceleration;
//#pragma region properties
//		geom::Point Position() const
//		{
//			return position;
//		}
//
//		void Position(geom::Point val)
//		{
//			position = val;
//		}
//
//		geom::Vector Velocity() const
//		{
//			return velocity;
//		}
//
//		void Velocity(geom::Vector val)
//		{
//			velocity = val;
//		}
//
//		geom::Vector Acceleration() const
//		{
//			return acceleration;
//		}
//
//		void Acceleration(geom::Vector val)
//		{
//			acceleration = val;
//		}
//#pragma endregion
//	protected:
//		geom::Point position;
//		geom::Vector velocity;
//		geom::Vector acceleration;
	};
}