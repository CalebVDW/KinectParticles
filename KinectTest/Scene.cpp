#include <iostream>
#include "Scene.h"


Scene::Scene(bool withoutSensor)
	:particles{ 10000 }, noSensor{ withoutSensor }
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
	float deltaTime = float(double(currentTime - previousTime) / double(SDL_GetPerformanceFrequency()));

	//Process Player input
	(this->*dataCollection)();
	
	//Add new particles that are created by emitters
	for (Emitter& e : emitters)
	{
		e.update(deltaTime);
		e.AddParticle(particles);
	}

	//Step through particles and update them
	

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
	skeletonData0 = skeletonFrame->SkeletonData[0];
	for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
	{
		if (skeletonFrame->SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED)
			skeletonData0 = skeletonFrame->SkeletonData[i];
	}
	//TODO//Create the skeleton objects
	/*
	rightHand.setPosition(Vector(firstSkeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x,
		firstSkeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y));
	leftHand.setPosition(Vector(firstSkeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].x,
		firstSkeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].y));
		*/
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
	
	for (int i = 0; i < NUI_SKELETON_COUNT; ++i)
	{
		//Draw the current skeleton
		if(skeletonFrame)
			drawSkeleton(skeletonFrame->SkeletonData[i]);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Scene::drawSkeleton(NUI_SKELETON_DATA skel)
{
	drawBone(skel, NUI_SKELETON_POSITION_HEAD, NUI_SKELETON_POSITION_SHOULDER_CENTER);
	drawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SHOULDER_RIGHT);
	drawBone(skel, NUI_SKELETON_POSITION_SHOULDER_CENTER, NUI_SKELETON_POSITION_SPINE);
	drawBone(skel, NUI_SKELETON_POSITION_SPINE, NUI_SKELETON_POSITION_HIP_CENTER);
	drawBone(skel, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_HIP_CENTER, NUI_SKELETON_POSITION_HIP_RIGHT);

	// Left Arm
	drawBone(skel, NUI_SKELETON_POSITION_SHOULDER_LEFT, NUI_SKELETON_POSITION_ELBOW_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_ELBOW_LEFT, NUI_SKELETON_POSITION_WRIST_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_WRIST_LEFT, NUI_SKELETON_POSITION_HAND_LEFT);

	// Right Arm
	drawBone(skel, NUI_SKELETON_POSITION_SHOULDER_RIGHT, NUI_SKELETON_POSITION_ELBOW_RIGHT);
	drawBone(skel, NUI_SKELETON_POSITION_ELBOW_RIGHT, NUI_SKELETON_POSITION_WRIST_RIGHT);
	drawBone(skel, NUI_SKELETON_POSITION_WRIST_RIGHT, NUI_SKELETON_POSITION_HAND_RIGHT);

	// Left Leg
	drawBone(skel, NUI_SKELETON_POSITION_HIP_LEFT, NUI_SKELETON_POSITION_KNEE_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_KNEE_LEFT, NUI_SKELETON_POSITION_ANKLE_LEFT);
	drawBone(skel, NUI_SKELETON_POSITION_ANKLE_LEFT, NUI_SKELETON_POSITION_FOOT_LEFT);

	// Right Leg
	drawBone(skel, NUI_SKELETON_POSITION_HIP_RIGHT, NUI_SKELETON_POSITION_KNEE_RIGHT);
	drawBone(skel, NUI_SKELETON_POSITION_KNEE_RIGHT, NUI_SKELETON_POSITION_ANKLE_RIGHT);
	drawBone(skel, NUI_SKELETON_POSITION_ANKLE_RIGHT, NUI_SKELETON_POSITION_FOOT_RIGHT);
}

void Scene::drawBone(NUI_SKELETON_DATA skel, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1)
{
	//Get joint positions
	int x1, y1, x2, y2;
	float skeletonScale = 400.0f;
	x1 = int(skeletonScale * skel.SkeletonPositions[joint0].x) + Constants::HALF_SCREEN_WIDTH;
	y1 = -int(skeletonScale * skel.SkeletonPositions[joint0].y) + Constants::HALF_SCREEN_HEIGHT;
	x2 = int(skeletonScale * skel.SkeletonPositions[joint1].x) + Constants::HALF_SCREEN_WIDTH;
	y2 = -int(skeletonScale * skel.SkeletonPositions[joint1].y) + Constants::HALF_SCREEN_HEIGHT;

	//Draw debug lines
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


Scene::~Scene()
{
}
