#pragma once
#include "Actor.h"

//Represents any object that has position and velocity and moves in the scene
//Could also be a stationary object in the case of walls or other objects
class PhysicsActor :
	public Actor
{
public:
	PhysicsActor(Transform t, float inverseMass, Vector velocity = Vector{}, float angularVelocity = 0);
	~PhysicsActor();

	void Update(float dt) override;

	//Public interface
	float InverseMass() const;
	float Mass() const;
	Vector Velocity() const;

protected:
	//Physics engine interface
	void ApplyForce(Vector force);
	void ApplyImpulse(Vector impulse);

private:
	Vector acceleration, velocity;
	float angularVelocity, angularAcceleration;
	float inverseMass;
};

