#include "PhysicsComponent.h"


void PhysicsComponent::update(float dt)
{
	//Linear stuff
	velocity += acceleration * dt;
	transform.move(velocity * dt);
	acceleration = glm::vec2();

	//Angular stuff
	angularVelocity += angularVelocity * dt;
	transform.rotate(angularVelocity * dt);
	angularAcceleration = 0;
}

void PhysicsComponent::applyForce(glm::vec2 force)
{
	acceleration += force;
}
void PhysicsComponent::applyImpulse(glm::vec2 impulse)
{
	velocity += impulse;
}

float PhysicsComponent::getInverseMass() const{ return inverseMass; }

PhysicsComponent::PhysicsComponent(Transform t, float inverseMass)
	:Actor{ t }, inverseMass{ inverseMass }
{
}


PhysicsComponent::~PhysicsComponent()
{
}
