#include "Emitter.h"


void Emitter::Update(float dt)
{
	Actor::Update(dt);
	//Spawn a particle if enough time has passed 
	timeSinceSpawn += dt;
	if (timeSinceSpawn > coolDownTime)
	{
		timeSinceSpawn = timeSinceSpawn - coolDownTime;
		particleReady = true;
	}
}

void Emitter::AddParticle(ParticleArray<Particle>& pArray)
{
	if (particleReady)
		pArray.Push(Particle(2.0f, color, transform.Position(), speed * direction));
	particleReady = false;
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
