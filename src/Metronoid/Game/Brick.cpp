#include "pch.h"
#include "Brick.h"
using namespace game;

Brick::Brick(void)
{
}

void Brick::Render(IMetronoidRenderer^ renderer)
{
	if(!IsDead)
	{
		geom::Rect destination(Position.X - Bounds.Width / 2, Position.Y - Bounds.Height / 2, Bounds.Width, Bounds.Height);

		renderer->FillRectangle(destination, FillColor);
	}
}

void Brick::ApplyCollisionEffect(GameObject^ object)
{
	if(object->Type == GameObjectType::Ball)
	{
		IsDead = true;
	}
}
