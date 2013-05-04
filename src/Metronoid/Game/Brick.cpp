#include "pch.h"
#include "Brick.h"

using namespace game;
using namespace Windows::UI;

Brick::Brick(void) 
{
	Health = 3;
	FullHealth = Health;
}

void Brick::Render(IMetronoidRenderer^ renderer)
{
	if(!IsDead)
	{
		geom::Rect destination(Position.X - Bounds.Width / 2, Position.Y - Bounds.Height / 2, Bounds.Width, Bounds.Height);

		Color fillColor = FillColor;

		fillColor.A = 255 * Health / FullHealth;

		renderer->FillRectangle(destination, fillColor);
	}
}

void Brick::ApplyCollisionEffect(GameObject^ object)
{
	if(object->Type == GameObjectType::Ball)
	{
		if(Health > 0)
		{
			Health--;
		}

		if(Health == 0)
		{
			IsDead = true;
		}
	}
}
