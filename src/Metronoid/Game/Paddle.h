#pragma once
#include "GameObject.h"
namespace game
{
	ref class Paddle : public GameObject
	{
	internal:
		Paddle();

		virtual void Step(float delta, geom::Point pointerPosition, geom::Size screenSize) override;
		virtual void Render(IMetronoidRenderer^ renderer) override;

		virtual property GameObjectType Type
		{
			GameObjectType get() override
			{
				return GameObjectType::Paddle;
			}
		}

		virtual property ShapeType Shape
		{
			ShapeType get() override
			{
				return ShapeType::Rectangle;
			}
		}
	};
}