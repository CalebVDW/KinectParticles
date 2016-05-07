#include "Target.h"



Target::Target(Transform t, float r, float inverseMass, Vector velocity)
	:PhysicsActor{ t, inverseMass, velocity }, radius{ r }, color{ 0, 0, 1.0f }, sprite{ "dot", 64, 64 }
{
}

bool Target::Collide(Particle* p)
{
	//Test intersection
	bool intersecting = math::CircleCollision(transform.Position(), p->GetTransform().Position(), radius, 0.005f);
	if (!intersecting)
		return false;

	//Apply impulse if applicable 
	ApplyImpulse(p->Velocity() / p->InverseMass());

	//Delete particle
	p->MarkForDelete();

	//Update color
	color.g += 0.01f;
	return true;
}

void Target::Update(float dt)
{
	PhysicsActor::Update(dt);
}

void Target::Render(SDL_Renderer* renderer)
{
	//Draw a circle to the screen 
	sprite.SetAlpha(alpha);
	sprite.SetTint(color);
	sprite.Render(renderer, transform.Position());
}

bool Target::Clear() const { return false; }


Target::~Target()
{
}
