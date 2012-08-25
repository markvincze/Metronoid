#include "pch.h"
#include "GameObject.h"
using namespace game;

GameObject::GameObject()
{
}

void GameObject::Step(float delta, geom::Point pointerPosition)
{
	this->Velocity += this->Acceleration * delta;
	this->Position += this->Velocity * delta;
}
