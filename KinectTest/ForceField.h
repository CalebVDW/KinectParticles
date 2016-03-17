#pragma once

#include "PhysicsComponent.h"

//This class will calculate a force based on the position of an object in the field
//It is nothing more than a programmable vector field
class ForceField
{
public:
	ForceField();
	~ForceField();

	glm::vec2 getForce(const PhysicsComponent& target) const;
	void setForceFunction(glm::vec2(*f)(const PhysicsComponent&));
private:
	glm::vec2(*forceFunction)(const PhysicsComponent&);

};

