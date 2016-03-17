#pragma once

#include "Actor.h"
#include "Particle.h"

//This will be a highly paramterized class that can emit various types of particles 
//All aspects of particle creation will be controlled here
//There should be no need to inherit from this class

//TODO//
//Figure out where spawned particles will be stored
class Emitter : public Actor
{
public:
	Emitter(Transform t);
	virtual ~Emitter();

	void update(float dt) override;

private:
	//These control the spawn paramteters of the particles
	glm::vec2 direction;
	float speed;
	glm::vec3 color;
	float spawnRate;		//Number of particles to spawn per second

	//Floats varying 0 - 1.0 
	//These determine how much random deviation there can be
	float directionVariation;
	float velocityVariation;
	glm::vec3 colorVariation;

};
