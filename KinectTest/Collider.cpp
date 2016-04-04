#include "Collider.h"



Collider::Collider(Transform t, float r)
	:Actor{ t }, radius{ r }
{
}

//Moves the collider to the owner actor's location
//Update should be called at the end of the update function for the owner actor
void Collider::update(float dt)
{
	transform.moveTo(owner->getTransform().Position());
	Actor::update(dt);
}

//Test intersection of 2 circle colliders
//Extends into 3+ dimensions depending on what vector type is used
bool Collider::testIntersection(const Collider& a)
{
	Vector difference = a.getTransform().Position() - transform.Position();
	float distSquare = glm::dot(difference, difference);
	float radiusSquare = math::square(a.getRadius() + radius);
	return radiusSquare > distSquare;
}


float Collider::getRadius() const { return radius; }


Collider::~Collider()
{
}
