#include "Particle.h"

float Particle::getInverseMass() const{ return inverseMass; }

void Particle::applyForce(glm::vec2 force)
{
	acceleration += force * inverseMass;
}
void Particle::applyImpulse(glm::vec2 impulse)
{
	velocity += impulse * inverseMass;
}

bool Particle::isAlive() const
{
	if (age > lifeSpan)
		return false;
}

//Returns false if the particle is dead
void Particle::update(float dt)
{
	//Update colors and stuff
	alpha = age / lifeSpan;
	age += dt;

	//Integration
	PhysicsComponent::update(dt);
}
void Particle::render(SDL_Renderer* renderer)
{
	//Convert to screen coordinates
	SDL_Rect drawRect;
	drawRect.x = int((position.x + 1.0f) * Constants::HALF_SCREEN_WIDTH);
	drawRect.y = int((-position.y + 1.0f) * Constants::HALF_SCREEN_HEIGHT);
	drawRect.w = 10;
	drawRect.h = 10;

	//Draw the rectangle
	SDL_SetRenderDrawColor(renderer, convertColor(color.x), convertColor(color.y), convertColor(color.z), convertColor(alpha));
	SDL_RenderDrawRect(renderer, &drawRect);
}

Particle::Particle(float life, glm::vec3 color, glm::vec2 pos, glm::vec2 velocity)
	:lifeSpan{ life }, color{ color }, position{ pos }, velocity{ velocity }
{
	inverseMass = 1.0f;
}


Particle::~Particle()
{
}
