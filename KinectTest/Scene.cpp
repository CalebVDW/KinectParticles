#include "Scene.h"

//Apply forces, resolve collisions, etc.
void Scene::update(NUI_SKELETON_FRAME* skeletonData)
{
	//Timekeeping stuff
	previousTime = currentTime;
	currentTime = SDL_GetPerformanceCounter();
	float deltaTime = float(double(currentTime - previousTime) / double(SDL_GetPerformanceFrequency()));

	//Get position of the player's right hand
	prevHandPos = handPos;
	handPos.x = myFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x;
	handPos.y = myFrame.SkeletonData[0].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y;

	//Spawn particles
	if (handPos != prevHandPos)
	{
		glm::vec2 pos = handPos;
		glm::vec2 velocity = handPos - prevHandPos;
		Particle temp{ 1.0f, glm::vec3(0, 1.0f, 0), pos, velocity * 10.0f };
		particles.push_back(temp);
	}
	//particles.push_back(Particle{ 1.0f, glm::vec3(1.0f, 0, 0), glm::vec2(), glm::vec2() });

	//Update all the particles and clear any that are dead
	for (int i = particles.size() - 1; i >= 0; i--)
	{
		if (particles[i].getInverseMass() != 0)
			particles[i].applyForce(glm::vec2(0, -0.2f) / particles[i].getInverseMass());
		particles[i].update(deltaTime);
		if (!particles[i].isAlive())
			particles.erase(particles.begin() + i);
	}
}

//Draw everything
void Scene::render(SDL_Renderer* renderer)
{
	//Draw everything
	SDL_RenderClear(renderer);
	for (Particle& p : particles)
	{
		p.render(renderer);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

Scene::Scene()
{
	//Create stuff here
	//This is a singleton class so don't worry about parameterizing anything
	currentTime = SDL_GetPerformanceCounter();
}


Scene::~Scene()
{
}
