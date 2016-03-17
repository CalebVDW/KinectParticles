#pragma once

#include <glm\glm.hpp>

//Not entirely sure why I am making a transform class
//I suppose position rotation and scale all still apply in 2D so this class will be helpful
class Transform
{
public:
	Transform();
	Transform(glm::vec2 p, float r, glm::vec2 s);
	~Transform();

	//Interface for owners
	void move(glm::vec2 offset);
	void moveTo(glm::vec2 p);
	void setRotation(float r);
	void rotate(float offset);
	void scale(glm::vec2 offset);
	void setScale(glm::vec2 s);

	//Public interface 
	float Rotation() const;
	glm::vec2 Scale() const;
	glm::vec2 Position() const;

private:
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;
};

