#include "Particle.h"

Particle::Particle()
	:lifeSpan{ 1.0f }, color{ glm::vec3(1.0f) }, PhysicsActor{ Transform(), 1.0f }, sprite{ "dot", 16, 16 }
{
	tailLength = 0;
	maxTailLength = 1.0f;
}

Particle::Particle(float life, glm::vec3 color, Vector pos, Vector velocity, float tailLength)
	: lifeSpan{ life }, color{ color }, PhysicsActor{ Transform{ pos }, 1.0f, velocity }, sprite{ "dot", 16, 16 }, maxTailLength{ tailLength }
{
	this->tailLength = 0;
	renderRadius = 5;
	age = 0;
}


float Particle::InverseMass() const{ return PhysicsActor::InverseMass(); }
Vector Particle::PreviousPosition() const { return previousPosition; }

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
void Particle::SetPosition(Vector p) { transform.SetPosition(p); }
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
	previousPosition = transform.Position();
	PhysicsActor::Update(dt);

	//Add current position to front of tail
	renderPositions.push_front(std::pair<Vector, float>(transform.Position(), dt));
	tailLength += dt;
	//Pop positions from the back of the tail if it is too long
	while (tailLength > maxTailLength)
	{
		tailLength -= renderPositions.back().second;
		renderPositions.pop_back();
	}
}

//TODO//Fix queue code so that trail length is independent of frame rate
void Particle::Render(SDL_Renderer* renderer)
{
	//Render positions is expected to contain all the correct positions at this point
	std::queue<std::pair<Vector, float>> tempQueue(renderPositions);

	//Render at each position in the trail
	while(tempQueue.size() > 0)
	{
		//Adjust alpha value of the sprite
		float trailScalar = float(tempQueue.size()) / float(renderPositions.size());
		sprite.SetAlpha(trailScalar);
		sprite.SetTint(glm::vec3(trailScalar, 1.0f, trailScalar));
		//Determine direction of particle and stretch sprites in that direction
		Vector direction = glm::normalize(Velocity());
		float angle = glm::acos(glm::dot(direction, glm::vec2(1.0f, 0)));
		angle *= (180.0f / 3.14159265f);
		if (direction.y > 0)
			angle = -angle;
		float scale = 4.0f * Velocity().length();
		sprite.Render(renderer, tempQueue.front().first, angle, glm::vec2(scale, 1.0f));
		tempQueue.pop();
	}
}


Particle::~Particle()
{
}
