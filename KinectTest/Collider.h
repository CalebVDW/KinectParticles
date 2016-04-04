#pragma once
#include "Actor.h"
class Collider :
	public Actor
{
public:
	Collider(Transform t, float r);
	~Collider();

	void update(float dt) override;
	bool testIntersection(const Collider& a);

	float getRadius() const;

private:
	Actor* owner;
	float radius;

};

