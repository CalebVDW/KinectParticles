#include "Actor.h"


const Transform& Actor::getTransform() const{ return transform; }
void Actor::update(float dt){ return; }

Actor::Actor(Transform t)
	:transform{ t }
{
}


Actor::~Actor()
{
}
