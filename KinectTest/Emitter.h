#pragma once

#include "Actor.h"
#include "Particle.h"
#include "ParticleArray.h"

//This will be a highly paramterized class that can emit various types of particles 
//All aspects of particle creation will be controlled here
//There should be no need to inherit from this class

//TODO//
//Figure out where spawned particles will be stored
class Emitter : public Actor
{
public:
	Emitter(Transform t, Vector direction, float rate = 1.0f, float speed = 1.0f);
	virtual ~Emitter();

	void update(float dt) override;
	void AddParticle(ParticleArray<Particle>& pArray);

private:
	//These control the spawn paramteters of the particles
	Vector direction;
	float speed;
	glm::vec3 color;
	float spawnRate;											//Number of particles to spawn per second
	float coolDownTime;
	float timeSinceSpawn;
	bool particleReady;

	//Store the next particle to be emitted
	Particle* nextParticle;

	//Floats varying 0 - 1.0 
	//These determine how much random deviation there can be
	float directionVariation;
	float velocityVariation;
	glm::vec3 colorVariation;

};
