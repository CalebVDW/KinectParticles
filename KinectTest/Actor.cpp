#include "Actor.h"


const Transform& Actor::GetTransform() const{ return transform; }
void Actor::Update(float dt){ return; }

Actor::Actor(Transform t)
	:transform{ t }
{
}


Actor::~Actor()
{
}
