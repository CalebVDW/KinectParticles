#include "Transform.h"


Transform::Transform()
{
}

Transform::Transform(glm::vec2 p, float r, glm::vec2 s)
	:position{ p }, rotation{ r }, scale{ s }
{
}


Transform::~Transform()
{
}
