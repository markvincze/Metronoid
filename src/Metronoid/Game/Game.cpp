#include "pch.h"
#include "Game.h"
#include <cstdlib>

using namespace game;
using namespace geom;

Game::Game(Size screenSize) :
	paddle(ref new Paddle()),
	screenSize(screenSize),
	balls(ref new Platform::Collections::Vector<Ball^>()),
	bricks(ref new Platform::Collections::Vector<Brick^>()),
	state(GameState::Starting),
	lives(3)
{
	paddle->Position = Point(screenSize.Width / 2, screenSize.Height - 50);

	backgroundColor.A = 255;
	backgroundColor.R = 255;
	backgroundColor.G = 255;
	backgroundColor.B = 255;

	ResetBalls();
	

	/*for (int i = 0; i < 10; i++)
	{
	Ball^ ball = ref new Ball();
	ball->Position = Point(screenSize.Width -600 + 50 * i, screenSize.Height - 80);
	ball->Velocity = Vector(60, -450 - 10 * i);
	balls->Append(ball);
	}*/

	/*Ball^ ball = ref new Ball();
	ball->Position = Point(227, 600);
	ball->Velocity = Vector(0, -50);
	ball->Bounds = Size(50, 50);
	balls->Append(ball);

	Brick^ brick = ref new Brick();
	brick->Position = Point(400, 400);
	brick->Bounds = Size(300, 300);
	brick->Velocity = Vector(0, 0);

	Windows::UI::Color fillColor;
	fillColor.A = 255;
	fillColor.R = 0;
	fillColor.G = 0x6D;
	fillColor.B = 0x13;
	brick->FillColor = fillColor;

	bricks->Append(brick);*/

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Brick^ brick = ref new Brick();
			brick->Position = Point(100 + i * 100, 100 + j * 100);
			brick->Bounds = Size(60, 60);
			brick->Velocity = Vector(0, 0);

			Windows::UI::Color fillColor;
			fillColor.A = 255;
			fillColor.R = 0;
			fillColor.G = 0x6D;
			fillColor.B = 0x13;
			brick->FillColor = fillColor;

			bricks->Append(brick);
		}
	}
}

void Game::Step(float delta, Point pointerPosition)
{
	if(state == GameState::Running)
	{
		StepBalls(delta, pointerPosition);

		// Ellen�rizz�k, hogy meghaltunk-e.
		bool died = true;
		for each (Ball^ ball in balls)
		{
			if(ball->Position.Y < screenSize.Height + ball->Bounds.Height / 2)
			{
				died = false;
				break;
			}
		}

		if(died)
		{
			ResetBalls();

			state = GameState::Starting;

			lives--;
		}
	}
	else if(state == GameState::Starting)
	{
		auto firstBall = balls->First()->Current;
		firstBall->Position = Point(paddle->Position.X, paddle->Position.Y - paddle->Bounds.Height / 2 - firstBall->Bounds.Width / 2 - 5);
	}

	paddle->Step(delta, pointerPosition, screenSize);
}

void Game::StepBalls(float delta, Point pointerPosition)
{
	for each(Ball^ ball in balls)
	{
		ball->CheckCollision(paddle);
		for each(Brick^ brick in bricks)
		{
			if(!brick->IsDead)
			{
				bool collided = ball->CheckCollision(brick);
				if(collided)
				{
					brick->ApplyCollisionEffect(ball);
				}
			}
		}

		ball->Step(delta, pointerPosition, screenSize);
	}
}

void Game::ResetBalls()
{
	balls->Clear();

	Ball^ ball = ref new Ball();
	ball->Position = Point(paddle->Position.X, paddle->Position.Y - paddle->Bounds.Height / 2 - ball->Bounds.Width / 2 - 5);
	balls->Append(ball);
}

void Game::Render(IMetronoidRenderer^ renderer)
{
	renderer->Clear(backgroundColor);

	for each(Brick^ brick in bricks)
	{
		brick->Render(renderer);
	}

	paddle->Render(renderer);

	for each(Ball^ ball in balls)
	{
		ball->Render(renderer);
	}

	auto firstBall = balls->First()->Current;

	renderer->DrawText(
		L"Ball velocity: " + firstBall->Velocity.X + L", " + firstBall->Velocity.Y +
		L" Length: " + firstBall->Velocity.Length,
		14,
		10,
		30,
		Windows::UI::Colors::Black);

	renderer->DrawText(
		L"Lives: " + lives,
		14,
		10,
		50,
		Windows::UI::Colors::Black);
}

void Game::Tapped(geom::Point position)
{
	if(state == GameState::Starting)
	{
		// V�letlenszer� ir�nyban indul a labda, 200 sebess�ggel.
		auto firstBall = balls->First()->Current;
		int velX = (rand() % 100) - 50;
		double velY = sqrt(50000 - velX * velX);
		firstBall->Velocity = Vector(velX, -velY);

		state = GameState::Running;
	}
}