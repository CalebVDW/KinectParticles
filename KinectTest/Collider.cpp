#include "Collider.h"



Collider::Collider(Transform t, float r)
	:Actor{ t }, radius{ r }
{
}

//Moves the collider to the owner actor's location
//Update should be called at the end of the update function for the owner actor
void Collider::Update(float dt)
{
	transform.SetPosition(owner->GetTransform().Position());
	Actor::Update(dt);
}

//Test intersection of 2 circle colliders
//Extends into 3+ dimensions depending on what vector type is used
bool Collider::TestIntersection(const Collider& a)
{
	Vector difference = a.GetTransform().Position() - transform.Position();
	float distSquare = glm::dot(difference, difference);
	float radiusSquare = math::square(a.Radius() + radius);
	return radiusSquare > distSquare;
}


float Collider::Radius() const { return radius; }


Collider::~Collider()
{
}
