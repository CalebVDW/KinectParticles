#include "Transform.h"


Transform::Transform()
{
}

Transform::Transform(Vector p)
	:position{ p }, orientation{ 0 }, scale{Vector(1.0f, 1.0f)}
{
}

Transform::Transform(Vector p, float r, Vector s)
	:position{ p }, orientation{ r }, scale{ s }
{
}

void Transform::move(Vector offset) { position += offset; }
void Transform::moveTo(Vector p) { position = p; }
void Transform::setRotation(float r) { orientation = r; }
void Transform::rotate(float offset) { orientation += offset; }
void Transform::setScale(Vector s) { scale = s; }

//Public interface 
float Transform::Rotation() const { return orientation; }
Vector Transform::Scale() const { return scale; }
Vector Transform::Position() const { return position; }


Transform::~Transform()
{
}
