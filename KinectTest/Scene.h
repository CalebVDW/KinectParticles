#pragma once

#include <list>
#include <vector>

#include <Windows.h>
#include <NuiApi.h>

#include "Particle.h"
#include "ForceField.h"

//A container for particles, emitters, skeletons and any other objects that the game needs
class Scene
{
public:
	Scene();
	~Scene();

	void update(NUI_SKELETON_FRAME* skeletonData);
	void render(SDL_Renderer* renderer);

private:
	//Scene content
	std::list<Particle> particles;
	std::vector<ForceField> fields;

	//Time keeping
	long long currentTime, previousTime;
};

