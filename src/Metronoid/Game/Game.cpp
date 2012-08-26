#include "pch.h"
#include "Game.h"
using namespace game;
using namespace geom;

Game::Game(Size screenSize) :
	paddle(ref new Paddle()),
	screenSize(screenSize),
	balls(ref new Platform::Collections::Vector<Ball^>())
{
	paddle->Position = Point(50, screenSize.Height / 2);

	Ball^ ball = ref new Ball();
	ball->Position = Point(screenSize.Width / 2, screenSize.Height / 2);
	ball->Velocity = Vector(500, 150);
	balls->Append(ball);
}

void Game::Step(float delta, Point pointerPosition)
{
	for each(Ball^ ball in balls)
	{
		ball->Collide(paddle);
		ball->Step(delta, pointerPosition, screenSize);
	}

	paddle->Step(delta, pointerPosition, screenSize);
}

void Game::Render(IMetronoidRenderer^ renderer)
{
	paddle->Render(renderer);

	for each(Ball^ ball in balls)
	{
		ball->Render(renderer);
	}
}