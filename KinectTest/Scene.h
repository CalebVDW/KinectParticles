#pragma once

#include <list>
#include <vector>

#include <Windows.h>
#include <NuiApi.h>

#include "Particle.h"
#include "KinematicActor.h"
#include "ForceField.h"
#include "Emitter.h"
#include "Target.h"
#include "ParticleArray.h"

//A container for particles, emitters, skeletons and any other objects that the game needs
//TODO//Refactor so that default constructor uses mouse input and parameterized constructor uses Kinect input
//This will also reduce the complexity of the code in main
class Scene
{
public:
	Scene(bool WithoutSensor = false);
	~Scene();

	void Update(NUI_SKELETON_FRAME* frame);
	void Render(SDL_Renderer* r);

private:
	bool noSensor;
	typedef void(Scene::*sceneProcedure)();
	sceneProcedure dataCollection;
	void getSensorData();
	void getMouseData();

	//Draw representation of the skeleton to the screen
	void drawSkeleton(NUI_SKELETON_DATA skel);

	//Draw a single bone to the screen
	void drawBone(NUI_SKELETON_DATA skel, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1);

	//Kinect Data that is updated every frame
	NUI_SKELETON_FRAME* skeletonFrame;
	NUI_SKELETON_DATA skeletonData0;
	NUI_SKELETON_DATA skeletonData1;

	//Rendering data
	SDL_Renderer* renderer;

	//Scene content
	ParticleArray<Particle> particles;
	std::vector<ForceField> fields;
	std::vector<Emitter> emitters;
	std::vector<Target> targets;

	//Time keeping
	long long currentTime, previousTime;
};

