#include "Emitter.h"


void Emitter::update(float dt)
{
	Actor::update(dt);
	//Spawn a particle if enough time has passed 
	timeSinceSpawn += dt;
	if (timeSinceSpawn > coolDownTime)
	{
		timeSinceSpawn = timeSinceSpawn - coolDownTime;
		createParticle();
	}
}

Particle* Emitter::getParticle()
{
	//Return the stored particle if there is one
	if (!nextParticle)
		return nullptr;
	Particle* temp = nextParticle;
	nextParticle = nullptr;
	return temp;
}

void Emitter::createParticle()
{
	//Create and store a new particle with the current parameters
	nextParticle = new Particle(2.0f, color, transform.Position(), speed * direction);
}

Emitter::Emitter(Transform t, Vector direction, float rate, float speed)
	:Actor{ t }, color{ 1.0f, 1.0f, 1.0f }, direction{ glm::normalize(direction) }, spawnRate {	rate}, speed{ speed }
{
	coolDownTime = 1.0f / spawnRate;
	timeSinceSpawn = 0;
	nextParticle = nullptr;
}

Emitter::~Emitter()
{
}
