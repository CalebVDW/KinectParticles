#include "ForceField.h"

Vector ForceFunctions::Gravity(const PhysicsActor& object, Vector origin)
{
	//Force is inversely proportional to the square of the distance between the objects
	Vector displacement = object.GetTransform().Position() - origin;
	float radiusSquare = glm::dot(displacement, displacement);
	return -displacement / (displacement.length() * radiusSquare);
}

Vector ForceFunctions::IncreasingLinearAttraction(const PhysicsActor& object, Vector origin)
{
	Vector displacement = object.GetTransform().Position() - origin;
	return -displacement / glm::dot(displacement, displacement);
}

Vector ForceFunctions::IncreasingLinearRepulsion(const PhysicsActor& object, Vector origin)
{
	Vector displacement = object.GetTransform().Position() - origin;
	return displacement / glm::dot(displacement, displacement);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Vector ForceField::GetForce(const PhysicsActor& target) const
{
	if (!forceFunction)
		return Vector();
	return fieldStrength * forceFunction(target, transform.Position());
}
void ForceField::SetForceFunction(Vector(*f)(const PhysicsActor& object, Vector origin))
{
	forceFunction = f;
}
void ForceField::SetFieldStrength(float f) { fieldStrength = f; }

ForceField::ForceField()
	:KinematicActor{ Transform() }
{
}


ForceField::~ForceField()
{
}
