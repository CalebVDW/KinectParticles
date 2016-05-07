#pragma once
#include <glm\glm.hpp>
#include <Windows.h>
#include <NuiApi.h>

//Using a typedef for the vector type in case I want to convert to 3D later
typedef glm::vec2 Vector;

namespace Constants
{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 800;

	const int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;
	const int HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2;
	const float FLT_SCREEN_WIDTH = float(SCREEN_WIDTH);
	const float FLT_SCREEN_HEIGHT = float(SCREEN_HEIGHT);
	const float FLT_HALF_SCREEN_WIDTH = float(HALF_SCREEN_WIDTH);
	const float FLT_HALF_SCREEN_HEIGHT = float(HALF_SCREEN_HEIGHT);

	const int MAX_PARTICLES = 10000;
}

//Putting constants and a few misc functions here
namespace math
{
	template<typename t>
	t square(t a)
	{
		return a * a;
	}
	//Converts NDC (physics/kinect space) to pixel coords for rendering with SDL
	void NdcToPixel(int& x, int& y, Vector pos);
	void NdcToPixel(float& x, float& y, Vector pos);

	//Converts pixel space to NDC 
	void PixelToNdc(Vector& result, int x, int y);

	//Determines if 2 circles are intersecting
	bool CircleCollision(Vector center1, Vector center2, float radius1, float radius2);

	float Cross2D(glm::vec2 a, glm::vec2 b);

	Vector MakeVector(Vector4 v);
}
