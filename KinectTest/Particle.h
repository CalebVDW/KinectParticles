#pragma once

#include "Constants.h"
#include "PhysicsComponent.h"

#include <SDL.h>

#include <glm\glm.hpp>

Uint8 inline convertColor(float a)
{
	return Uint8(255.0f * a);
}

class Particle : public PhysicsComponent
{
public:
	Particle(float lifeSpan, glm::vec3 color, glm::vec2 pos, glm::vec2 velocity);
	virtual ~Particle();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	//Getters
	float getInverseMass() const;
	bool isAlive() const;

private:
	//Rendering data
	glm::vec3 color;
	float alpha;

	//Creation destruction stuff
	float lifeSpan;
	float age;
};

