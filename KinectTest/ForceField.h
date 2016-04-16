#pragma once

#include "PhysicsActor.h"
#include "KinematicActor.h"
#include "Constants.h"

//These functions return a force vector to be applied to an object based on the objects position and the field origin
namespace ForceFunctions {
	//Force Function that mimics gravity -- inversely proportional to the square of the distance
	Vector Gravity(const PhysicsActor& objects, Vector origin);
	//Force that increases linearly as objects get closer. Similar to gravity but will not cause objects to orbit in the same way 
	Vector IncreasingLinearAttraction(const PhysicsActor& object, Vector origin);
	//Repelling force that increases linearly as objects get closer
	Vector IncreasingLinearRepulsion(const PhysicsActor& object, Vector origin);
}

//This class will calculate a force based on the position of an object in the field
//It is nothing more than a programmable vector field over R2
class ForceField : public KinematicActor
{
public:
	ForceField();
	~ForceField();

	Vector GetForce(const PhysicsActor& target) const;
	void SetForceFunction(Vector(*f)(const PhysicsActor& object, Vector origin));
	void SetFieldStrength(float f);

private:
	Vector(*forceFunction)(const PhysicsActor& object, Vector origin);
	float fieldStrength = 1.0f;
};

