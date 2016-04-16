#include <iostream>
#include "Scene.h"


Scene::Scene(bool withoutSensor)
	:particles{ Constants::MAX_PARTICLES }, noSensor{ withoutSensor }
{
	dataCollection = noSensor ? &Scene::getMouseData : &Scene::getSensorData;

	//Create stuff here
	currentTime = SDL_GetPerformanceCounter();

	//Emitters
	emitters.push_back(Emitter(Transform(Vector(-1.0f, 0)), Vector(1.0f, 0), 10.0f, 0.5f));

	//Targets
	targets.push_back(Target(Transform(Vector(0, 0.8f)), 0.1f));
}


//Apply forces, resolve collisions, etc.
void Scene::Update(NUI_SKELETON_FRAME* frame)
{
	//Update kinect data
	skeletonFrame = frame;

	//Timekeeping stuff
	previousTime = currentTime;
	currentTime = SDL_GetPerformanceCounter();
	deltaTime = float(double(currentTime - previousTime) / double(SDL_GetPerformanceFrequency()));

	//Process Player input
	(this->*dataCollection)();
	
	//Add new particles that are created by emitters
	for (Emitter& e : emitters)
	{
		e.update(deltaTime);
		e.AddParticle(particles);
	}

	//Step through particles and update them
	for (int i = 0; i < particles.Size(); ++i)
	{
		particles[i].update(deltaTime);
	}

	//Delete particles that have exceeded their lifespan
	particles.RemoveElements([](const Particle& p)->bool {return p.isAlive(); });

	//Step through targets
	for (Target& target : targets)
	{
		//Check particle collisions with target
		for (int i = 0; i < particles.Size(); ++i)
		{
			target.collide(&particles[i]);
		}
		
		//Update target's location
		target.update(deltaTime);
	}
}

void Scene::getMouseData()
{

}

void Scene::getSensorData()
{
	//Find first tracked skeleton
	int index0 = 0;
	for (; index0 < NUI_SKELETON_COUNT; ++index0)
	{
		if (skeletonFrame->SkeletonData[index0].eTrackingState == NUI_SKELETON_TRACKED)
			break;
	}
	//Find second tracked skeleton
	int index1 = index0 + 1;
	for (; index1 < NUI_SKELETON_COUNT; ++index1)
	{
		if (skeletonFrame->SkeletonData[index1].eTrackingState == NUI_SKELETON_TRACKED)
			break;
	}
	//Update player skeletons if skeletons were found
	if (index0 < NUI_SKELETON_COUNT)
		player0.Update(deltaTime, skeletonFrame->SkeletonData[index0]);
	else
		player0.Deactivate();
	if (index1 < NUI_SKELETON_COUNT)
		player1.Update(deltaTime, skeletonFrame->SkeletonData[index1]);
	else
		player1.Deactivate();
}

//Draw everything
void Scene::Render(SDL_Renderer* r)
{
	renderer = r;
	SDL_RenderClear(renderer);
	//Draw particles
	for (int i = 0; i < particles.Size(); ++i)
	{
		particles[i].render(renderer);
	}

	//Draw targets
	for (Target& target : targets)
	{
		target.render(renderer);
	}

	//Draw skeleton
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	player0.Render(renderer);
	player1.Render(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}


Scene::~Scene()
{
}
