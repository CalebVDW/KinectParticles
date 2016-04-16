#include "Target.h"



Target::Target(Transform t, float r, float inverseMass, Vector velocity)
	:PhysicsActor{ t, inverseMass, velocity }, radius{ r }, color{ 0, 0, 1.0f }
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
	SDL_Rect drawRect;
	math::NdcToPixel(drawRect.x, drawRect.y, transform.Position());

	//Offset the drawrect so that it is centered over the Particle
	drawRect.x -= int(radius * Constants::FLT_HALF_SCREEN_WIDTH);
	drawRect.y -= int(radius * Constants::FLT_HALF_SCREEN_HEIGHT);

	drawRect.w = int(radius * Constants::FLT_SCREEN_WIDTH);
	drawRect.h = int(radius * Constants::FLT_SCREEN_HEIGHT);

	//Draw the rectangle
	SDL_SetRenderDrawColor(renderer, convertColor(color.x), convertColor(color.y), convertColor(color.z), convertColor(alpha));
	SDL_RenderDrawRect(renderer, &drawRect);
}


Target::~Target()
{
}
