#pragma once

#include "Transform.h"

//A thin wrapper for a transform
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

