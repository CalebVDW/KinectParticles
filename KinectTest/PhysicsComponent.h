#pragma once
#include "Actor.h"

//Because this simulation will be limited to circle colliders, I have decided to implement this as 
//physics handler and collision handler combined
class PhysicsComponent :
	public Actor
{
public:
	PhysicsComponent(Transform t, float inverseMass);
	~PhysicsComponent();

	void update(float dt) override;

protected:
	//Physics engine interface
	void applyForce(glm::vec2 force);
	void applyImpulse(glm::vec2 impulse);
	
	//Public interface
	float getInverseMass() const;

private:
	glm::vec2 acceleration, velocity;
	float angularVelocity, angularAcceleration;
	float inverseMass;
	float radius;
};

