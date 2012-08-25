#pragma once
#include "../Interfaces/IMetronoidRenderer.h"
#include "../Geometry/Point.h"
#include "Paddle.h"
namespace game
{
	ref class Game
	{
	internal:
		Game();

		void Step(float delta, geom::Point pointerPosition);
		void Render(IMetronoidRenderer^ renderer);

	private:
		Paddle^ paddle;
	};
}