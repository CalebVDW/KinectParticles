#pragma once
#include "Actor.h"
class Collider :
	public Actor
{
public:
	Collider(Transform t, float r);
	~Collider();

	void Update(float dt) override;
	bool TestIntersection(const Collider& a);

	float Radius() const;

private:
	Actor* owner;
	float radius;

};

