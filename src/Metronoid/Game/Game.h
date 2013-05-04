#pragma once

#include "../Interfaces/IMetronoidRenderer.h"
#include "../Geometry/Point.h"
#include "../Geometry/Size.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "GameState.h"

namespace game
{
	ref class Game
	{
	internal:
		Game(geom::Size screenSize);

		void Step(float delta, geom::Point pointerPosition);

		void Render(IMetronoidRenderer^ renderer);

		void Tapped(geom::Point position);
		
	private:
		void StepBalls(float delta, geom::Point pointerPosition);

		void ResetBalls();

		Paddle^ paddle;

		geom::Size screenSize;

		Platform::Collections::Vector<Ball^>^ balls;

		Platform::Collections::Vector<Brick^>^ bricks;

		GameState state;

		int lives;

		Windows::UI::Color backgroundColor;
	};
}