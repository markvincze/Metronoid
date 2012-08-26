#include "pch.h"
#include "GameObject.h"
using namespace game;

GameObject::GameObject()
{
	LastCollision = 0;
}

void GameObject::Step(float delta, geom::Point pointerPosition, geom::Size screenSize)
{
	this->Velocity += this->Acceleration * delta;
	this->Position += this->Velocity * delta;
}
