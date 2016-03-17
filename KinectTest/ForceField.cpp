#include "ForceField.h"

glm::vec2 ForceField::getForce(const PhysicsComponent& target) const
{
	if (!forceFunction)
		return glm::vec2();
	return forceFunction(target);
}
void ForceField::setForceFunction(glm::vec2(*f)(const PhysicsComponent&))
{
	forceFunction = f;
}

ForceField::ForceField()
{
}


ForceField::~ForceField()
{
}
