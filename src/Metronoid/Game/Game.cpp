#include "pch.h"
#include "Game.h"
using namespace game;
using namespace geom;

Game::Game(Size screenSize) :
	paddle(ref new Paddle()),
	screenSize(screenSize),
	balls(ref new Platform::Collections::Vector<Ball^>()),
	bricks(ref new Platform::Collections::Vector<Brick^>())
{
	paddle->Position = Point(50, screenSize.Height / 2);

	backgroundColor.A = 255;
	backgroundColor.R = 255;
	backgroundColor.G = 255;
	backgroundColor.B = 255;

	Ball^ ball = ref new Ball();
	ball->Position = Point(screenSize.Width -600, screenSize.Height - 80);
	ball->Velocity = Vector(400, 150);
	balls->Append(ball);

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

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Brick^ brick = ref new Brick();
			brick->Position = Point(400 + i * 100, 100 + j * 100);
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

	paddle->Step(delta, pointerPosition, screenSize);
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
}