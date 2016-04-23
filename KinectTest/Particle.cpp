#include "Particle.h"

Particle::Particle()
	:lifeSpan{ 1.0f }, color{ glm::vec3(1.0f) }, PhysicsActor{ Transform(), 1.0f }, sprite{ "dot", 16, 16 }
{

}

Particle::Particle(float life, glm::vec3 color, Vector pos, Vector velocity, Uint32 tailLength)
	: lifeSpan{ life }, color{ color }, PhysicsActor{ Transform{ pos }, 1.0f, velocity }, sprite{ "dot", 16, 16 }
{
	renderPositions = std::deque<Vector>(tailLength, Vector(10.0f, 10.0f));
	renderRadius = 5;
	age = 0;
}


float Particle::InverseMass() const{ return PhysicsActor::InverseMass(); }

void Particle::ApplyForce(Vector force)
{
	PhysicsActor::ApplyForce(force);
}
void Particle::ApplyImpulse(Vector impulse)
{
	PhysicsActor::ApplyImpulse(impulse);
}
void Particle::MarkForDelete()
{
	//Marking for delete is implemented by setting the age beyond the limit
	//This implementation will most likely stay in the long run 
	age += lifeSpan;
}

bool Particle::IsAlive() const
{
	if (age > lifeSpan)
		return false;
	return true;
}

//Returns false if the particle is dead
void Particle::Update(float dt)
{
	//Update colors and stuff
	age += dt;

	//Integration
	PhysicsActor::Update(dt);
}

//TODO//Fix queue code so that trail length is independent of frame rate
void Particle::Render(SDL_Renderer* renderer)
{
	//Update previous positions queue
	renderPositions.push_front(transform.Position());
	renderPositions.pop_back();
	std::queue<Vector> tempQueue(renderPositions);

	//Render at each position in the trail
	while(tempQueue.size() > 0)
	{
		//Render a sprite at the current position and remove that position from the queue
		sprite.Render(renderer, tempQueue.front());
		tempQueue.pop();
	}
}


Particle::~Particle()
{
}
