#pragma once
#include "Actor.h"

//An actor whose motion is not controlled by the physics system
//Provides direct access to the transform
class KinematicActor :
	public Actor
{
public:
	KinematicActor();
	KinematicActor(Transform t);
	~KinematicActor();

	void setPosition(Vector p);
	void setRotation(float angle);
	
	void translate(Vector offset);
	void rotate(float angle);
};

