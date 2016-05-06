#include "RotatingTarget.h"



RotatingTarget::RotatingTarget(Transform t, float r, float inverseMass, Vector velocity)
	:Target{ t, r, inverseMass, velocity }, innerSprite{ "inner", 64, 64 }, middleSprite{ "middle", 92, 92 }, outerSprite{ "outer", 128, 128 }
{

}

bool RotatingTarget::Collide(Particle* p)
{
	bool intersecting = math::CircleCollision(transform.Position(), p->GetTransform().Position(), radius, 0.005f);
	if (!intersecting)
		return false;

	//Apply impulse if applicable 
	//ApplyImpulse(p->Velocity() / p->InverseMass());
	ApplyAngularImpulse(p->Velocity().length() * (p->InverseMass() / 10.0f));

	//Apply drag force
	//ApplyAngularImpulse()

	//Delete particle
	p->MarkForDelete();
}

void RotatingTarget::Update(float dt)
{
	Target::Update(dt);
}
void RotatingTarget::Render(SDL_Renderer* renderer)
{
	innerSprite.Render(renderer, transform.Position(), transform.Rotation());
	middleSprite.Render(renderer, transform.Position(), -transform.Rotation());
	outerSprite.Render(renderer, transform.Position(), transform.Rotation());
}


RotatingTarget::~RotatingTarget()
{
}
