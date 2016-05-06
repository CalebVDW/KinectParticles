#pragma once

#include "Particle.h"

//A target is an object that particles can interact with
//May be stationary or moveable. That is determined by the inverse mass
class Target : public PhysicsActor
{
public:
	Target(Transform t, float r, float inverseMass = 0, Vector velocity = Vector());
	~Target();

	//This tests intersection with a particle and deletes it if an intersection is detected
	//This interface will need to be overhauled soon 
	virtual bool Collide(Particle* p);
	void Update(float dt) override;
	virtual void Render(SDL_Renderer* renderer);

protected:
	float radius;
	glm::vec3 color;
	float alpha = 1.0f;
private:
	Sprite sprite;
};

