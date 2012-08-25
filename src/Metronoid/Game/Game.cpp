#include "pch.h"
#include "Game.h"
using namespace game;

Game::Game() :
	paddle(ref new Paddle())
{
}

void Game::Step(float delta, geom::Point pointerPosition)
{
	paddle->Step(delta, pointerPosition);
}

void Game::Render(IMetronoidRenderer^ renderer)
{
	paddle->Render(renderer);
}