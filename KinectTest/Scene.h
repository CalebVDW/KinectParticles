#pragma once

#include <list>
#include <vector>
#include <string>

#include "Constants.h"
#include "Particle.h"
#include "KinematicActor.h"
#include "ForceField.h"
#include "Emitter.h"
#include "Target.h"
#include "ParticleArray.h"
#include "Skeleton.h"

//A container for particles, emitters, skeletons and any other objects that the game needs
//TODO//Refactor so that default constructor uses mouse input and parameterized constructor uses Kinect input
//This will also reduce the complexity of the code in main
class Scene
{
public:
	Scene(SDL_Renderer* renderer, bool withoutSensor = false);
	Scene(SDL_Renderer* renderer, std::string mapFilePath, bool withoutSensor = false);
	~Scene();

	void Update(NUI_SKELETON_FRAME* frame);
	void Render(SDL_Renderer* r);

private:
	bool noSensor;
	float deltaTime;
	typedef void(Scene::*sceneProcedure)();
	sceneProcedure dataCollection;
	void getSensorData();
	void getMouseData();

	//Kinect Data that is updated every frame
	NUI_SKELETON_FRAME* skeletonFrame;
	Skeleton player0;
	Skeleton player1;

	//Rendering data
	SDL_Renderer* renderer;

	//Scene content
	ParticleArray<Particle> particles;
	std::vector<ForceField> fields;
	std::vector<Emitter> emitters;
	std::vector<Target> targets;

	//Time keeping
	long long currentTime, previousTime;

	//Helper functions
	void loadAssets();
	void parseMapFile(std::string path);
	void parseEmitterLine(std::string line);
	void parseTargetLine(std::string line);
	float popNextFloat(std::string& line);

};

