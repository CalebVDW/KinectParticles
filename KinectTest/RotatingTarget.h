#pragma once
#include "Target.h"
class RotatingTarget :
	public Target
{
public:
	RotatingTarget(Transform t, float r, float inverseMass = 10.0f, Vector velocity = Vector());
	~RotatingTarget();

	bool Collide(Particle* p) override;
	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
	bool Clear() const override;

private:
	Sprite innerSprite;
	Sprite middleSprite;
	Sprite outerSprite;

};

