#pragma once

#include "Transform.h"

//A thin wrapper for a transform
//Any object in the scene that has a position

//TODO//Add a parent child system
//There will be an origin transform that is used to compute the final transform
//Update can take in the parent and update the origin transform
class Actor
{
public:
	Actor(Transform t);
	virtual ~Actor();

	const Transform& getTransform() const;

	virtual void update(float dt);

protected:
	Transform transform;
};

