#pragma once
#include "GameObject.h"
namespace game
{
	ref class Ball : public GameObject
	{
	internal:
		Ball(void);

		virtual void Step(float delta, geom::Point pointerPosition, geom::Size screenSize) override;
		virtual void Render(IMetronoidRenderer^ renderer) override;

		virtual property GameObjectType Type
		{
			GameObjectType get() override
			{
				return GameObjectType::Ball;
			}
		}

		virtual property ShapeType Shape
		{
			ShapeType get() override
			{
				return ShapeType::Ellipse;
			}
		}
	};
}