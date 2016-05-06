#include "PhysicsActor.h"


void PhysicsActor::Update(float dt)
{
	//Linear integration
	velocity += acceleration * dt;
	transform.Translate(velocity * dt);
	acceleration = Vector();

	//Angular integration
	angularVelocity += angularAcceleration * dt;
	transform.Rotate(angularVelocity * dt);
	angularAcceleration = 0;
}

//Owner actor interface////////////////////////////////////////////////////////
void PhysicsActor::ApplyForce(Vector force)
{
	acceleration += force * inverseMass;
}
void PhysicsActor::ApplyImpulse(Vector impulse)
{
	velocity += impulse * inverseMass;
}

void PhysicsActor::ApplyTorque(float amt)
{
	angularAcceleration += amt * inverseMass;
}
void PhysicsActor::ApplyAngularImpulse(float amt)
{
	angularVelocity += amt * inverseMass;
}

//Const interface//////////////////////////////////////////////////////////////
float PhysicsActor::InverseMass() const{ return inverseMass; }
float PhysicsActor::Mass() const 
{ 
	if (inverseMass == 0) 
		return FLT_MAX; 
	else 
		return 1.0f / inverseMass; 
}
float PhysicsActor::AngularVelocity() const { return angularVelocity; }
Vector PhysicsActor::Velocity() const { return velocity; }

PhysicsActor::PhysicsActor(Transform t, float inverseMass, Vector v, float angularVelocity)
	:Actor{ t }, inverseMass{ inverseMass }, velocity{ v }, angularVelocity{ angularVelocity }
{
}

///////////////////////////////////////////////////////////////////////////////
PhysicsActor::~PhysicsActor()
{
}
