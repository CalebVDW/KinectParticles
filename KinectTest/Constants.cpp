#include "Constants.h"

void math::NdcToPixel(int& x, int& y, Vector pos)
{
	x = int(Constants::FLT_HALF_SCREEN_WIDTH * pos.x) + Constants::HALF_SCREEN_WIDTH;
	y = int(-Constants::FLT_HALF_SCREEN_HEIGHT * pos.y) + Constants::HALF_SCREEN_HEIGHT;
}
void math::NdcToPixel(float& x, float& y, Vector pos)
{
	x = Constants::FLT_HALF_SCREEN_WIDTH * pos.x + Constants::FLT_HALF_SCREEN_WIDTH;
	y = -Constants::FLT_HALF_SCREEN_HEIGHT * pos.y + Constants::FLT_HALF_SCREEN_HEIGHT;
}
void math::PixelToNdc(Vector& result, int x, int y)
{
	result.x = (float(x) - Constants::FLT_HALF_SCREEN_WIDTH) / Constants::FLT_HALF_SCREEN_WIDTH;
	result.y = (float(y) - Constants::FLT_HALF_SCREEN_HEIGHT) / -Constants::FLT_HALF_SCREEN_HEIGHT;
}
//Determines if 2 circles are intersecting
bool math::CircleCollision(Vector center1, Vector center2, float radius1, float radius2)
{
	Vector difference = center1 - center2;
	float distSquare = glm::dot(difference, difference);
	float radiusSquare = math::square(radius1 + radius2);
	return radiusSquare > distSquare;
}

Vector math::MakeVector(Vector4 v) { return Vector{ v.x, v.y }; }