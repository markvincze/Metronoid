#pragma once
#include "../Interfaces/IMetronoidRenderer.h"
#include "../Geometry/Point.h"
#include "../Geometry/Size.h"
#include "Ball.h"
#include "Paddle.h"
namespace game
{
	ref class Game
	{
	internal:
		Game(geom::Size screenSize);

		void Step(float delta, geom::Point pointerPosition);
		void Render(IMetronoidRenderer^ renderer);
		
	private:
		Paddle^ paddle;
		geom::Size screenSize;
		Platform::Collections::Vector<Ball^>^ balls;
		Windows::UI::Color backgroundColor;
	};
}