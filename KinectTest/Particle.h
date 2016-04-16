#pragma once

#include "Constants.h"
#include "PhysicsActor.h"

#include <SDL.h>
#include <deque>
#include <queue>

#include <glm\glm.hpp>

Uint8 inline convertColor(float a)
{
	return Uint8(255.0f * a);
}

//Defines an object that is spawned, has a limited life span, and interacts with the physics system
//Does not necessarily collide with other particles

//Particles are lightweight and passed by value. They do not hold any resources that need to be released
class Particle : public PhysicsActor
{
public:
	Particle();
	Particle(float lifeSpan, glm::vec3 color, Vector pos, Vector velocity, Uint32 tailLength = 100);
	virtual ~Particle();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	//Physics interface is made public for particles
	void applyForce(Vector f);
	void applyImpulse(Vector f);
	void markForDelete();

	//Const interface
	bool isAlive() const;
	float getInverseMass() const;

private:
	//Rendering data
	glm::vec3 color;
	float alpha;
	int renderRadius;
	std::deque<Vector> renderPositions;

	//Creation destruction stuff
	float lifeSpan;
	float age;
};

