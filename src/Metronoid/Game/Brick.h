#pragma once
#include "GameObject.h"
namespace game
{
	ref class Brick : public GameObject
	{
	internal:
		Brick(void);
		virtual void Render(IMetronoidRenderer^ renderer) override;
		virtual void ApplyCollisionEffect(GameObject^ object) override;

		property bool IsDead;

		virtual property GameObjectType Type
		{
			GameObjectType get() override
			{
				return GameObjectType::Brick;
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