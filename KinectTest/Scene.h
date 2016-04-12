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
class Scene
{
public:
	Scene();
	~Scene();

	void update(NUI_SKELETON_FRAME* frame);
	void render(SDL_Renderer* r);

private:
	//Draw representation of the skeleton to the screen
	void drawSkeleton(NUI_SKELETON_DATA skel);

	//Draw a single bone to the screen
	void drawBone(NUI_SKELETON_DATA skel, NUI_SKELETON_POSITION_INDEX joint0, NUI_SKELETON_POSITION_INDEX joint1);

	//Kinect Data that is updated every frame
	NUI_SKELETON_FRAME* skeletonFrame;

	//Rendering data
	SDL_Renderer* renderer;

	//Scene content
	ParticleArray<Particle> particles;
	std::vector<ForceField> fields;
	std::vector<Emitter> emitters;
	std::vector<Target> targets;

	//Hands will simply be kinematic actors that have things added as children
	KinematicActor rightHand;
	KinematicActor leftHand;

	//Time keeping
	long long currentTime, previousTime;
};

