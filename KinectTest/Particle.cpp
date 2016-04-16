#include "Particle.h"

Particle::Particle()
	:lifeSpan{ 1.0f }, color{ glm::vec3(1.0f) }, PhysicsActor{ Transform(), 1.0f }
{

}

Particle::Particle(float life, glm::vec3 color, Vector pos, Vector velocity)
	:lifeSpan{ life }, color{ color }, PhysicsActor{ Transform{ pos }, 1.0f, velocity }
{
	renderRadius = 5;
	age = 0;
}


float Particle::getInverseMass() const{ return PhysicsActor::getInverseMass(); }

void Particle::applyForce(Vector force)
{
	PhysicsActor::applyForce(force);
}
void Particle::applyImpulse(Vector impulse)
{
	PhysicsActor::applyImpulse(impulse);
}
void Particle::markForDelete()
{
	//Marking for delete is implemented by setting the age beyond the limit
	//This implementation will most likely stay in the long run 
	age += lifeSpan;
}

bool Particle::isAlive() const
{
	if (age > lifeSpan)
		return false;
	return true;
}

//Returns false if the particle is dead
void Particle::update(float dt)
{
	//Update colors and stuff
	age += dt;

	//Integration
	PhysicsActor::update(dt);
}
void Particle::render(SDL_Renderer* renderer)
{
	//Convert to screen coordinates
	SDL_Rect drawRect;
	math::NdcToPixel(drawRect.x, drawRect.y, transform.Position());

	//Offset the drawrect so that it is centered over the Particle
	drawRect.x -= renderRadius;
	drawRect.y -= renderRadius;

	drawRect.w = renderRadius * 2;
	drawRect.h = renderRadius * 2;

	//Draw the rectangle
	SDL_SetRenderDrawColor(renderer, convertColor(color.x), convertColor(color.y), convertColor(color.z), convertColor(alpha));
	SDL_RenderDrawRect(renderer, &drawRect);
}


Particle::~Particle()
{
}
