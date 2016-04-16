#pragma once

#include <glm\glm.hpp>
#include "Constants.h"

//Not entirely sure why I am making a transform class
//I suppose position rotation and scale all still apply in 2D so this class will be helpful
class Transform
{
public:
	Transform();
	Transform(Vector p);
	Transform(Vector p, float r, Vector s);
	~Transform();

	//Interface for owners
	void Translate(Vector offset);
	void SetPosition(Vector p);
	void SetRotation(float r);
	void Rotate(float offset);
	void SetScale(Vector s);

	//Public interface 
	float Rotation() const;
	Vector Scale() const;
	Vector Position() const;

private:
	Vector position;
	Vector scale;
	float orientation;
};

