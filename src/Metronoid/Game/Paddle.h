#pragma once
#include "GameObject.h"
namespace game
{
	ref class Paddle : public GameObject
	{
	internal:
		Paddle();

		virtual void Step(float delta, geom::Point pointerPosition) override;
		virtual void Collide(GameObject^ object) override;
		virtual void Render(IMetronoidRenderer^ renderer) override;
	};
}