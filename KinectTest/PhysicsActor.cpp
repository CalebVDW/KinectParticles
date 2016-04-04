#include "PhysicsActor.h"


void PhysicsActor::update(float dt)
{
	//Linear integration
	velocity += acceleration * dt;
	transform.move(velocity * dt);
	acceleration = Vector();

	//Angular integration
	angularVelocity += angularVelocity * dt;
	transform.rotate(angularVelocity * dt);
	angularAcceleration = 0;
}

//Owner actor interface////////////////////////////////////////////////////////
void PhysicsActor::applyForce(Vector force)
{
	acceleration += force * inverseMass;
}
void PhysicsActor::applyImpulse(Vector impulse)
{
	velocity += impulse * inverseMass;
}

//Const interface//////////////////////////////////////////////////////////////
float PhysicsActor::getInverseMass() const{ return inverseMass; }
float PhysicsActor::getMass() const 
{ 
	if (inverseMass == 0) 
		return FLT_MAX; 
	else 
		return 1.0f / inverseMass; 
}
Vector PhysicsActor::getVelocity() const { return velocity; }

PhysicsActor::PhysicsActor(Transform t, float inverseMass, Vector v, float angularVelocity)
	:Actor{ t }, inverseMass{ inverseMass }, velocity{ v }, angularVelocity{ angularVelocity }
{
}

///////////////////////////////////////////////////////////////////////////////
PhysicsActor::~PhysicsActor()
{
}
