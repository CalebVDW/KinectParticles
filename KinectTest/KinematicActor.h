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

	void SetPosition(Vector p);
	void SetRotation(float angle);
	
	void Translate(Vector offset);
	void Rotate(float angle);
};

