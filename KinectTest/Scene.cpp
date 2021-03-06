#include <iostream>
#include "Scene.h"


Scene::Scene(SDL_Renderer* renderer, SDL_Texture* targetTexture, bool withoutSensor)
	:particles{ Constants::MAX_PARTICLES }, renderer{ renderer }, targetTexture { targetTexture }, noSensor{ withoutSensor }
{
	dataCollection = noSensor ? &Scene::getMouseData : &Scene::getSensorData;
	SDL_SetRenderTarget(renderer, targetTexture);
	SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);
	loadAssets();	
	buildDefaultLevel();
	currentTime = SDL_GetPerformanceCounter();
}

Scene::Scene(SDL_Renderer* renderer, SDL_Texture* targetTexture, std::string mapFilePath, bool withoutSensor)
	:particles{ Constants::MAX_PARTICLES }, renderer{ renderer }, targetTexture{ targetTexture }, noSensor{ withoutSensor }
{
	dataCollection = noSensor ? &Scene::getMouseData : &Scene::getSensorData;
	SDL_SetRenderTarget(renderer, targetTexture);
	SDL_SetTextureBlendMode(targetTexture, SDL_BLENDMODE_BLEND);
	loadAssets();
	parseMapFile(mapFilePath);
	currentTime = SDL_GetPerformanceCounter();
}

void Scene::loadAssets()
{
	std::string spriteDir = "Sprites/";
	StaticResources::LoadPNG(spriteDir + "dot.png", "dot");
	StaticResources::LoadPNG(spriteDir + "inner.png", "inner");
	StaticResources::LoadPNG(spriteDir + "middle.png", "middle");
	StaticResources::LoadPNG(spriteDir + "outer.png", "outer");
	StaticResources::LoadPNG(spriteDir + "flare.png", "flare");
}

void Scene::buildDefaultLevel()
{
	//Emitters
	emitters.push_back(new Emitter(Transform(Vector(-1.0f, 0)), Vector(1.0f, 0), 5.0f, 0.2f));

	//Targets
	targets.push_back(new RotatingTarget(Transform(Vector(0, 0.8f)), 0.1f));
}

void Scene::parseMapFile(std::string path)
{
	//Step through each line of the file
	std::string line;
	std::ifstream file(path);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			//Check the first word of each line to see what kind of object to make
			if (line.find("Emitter", 0) == 0)
				parseEmitterLine(line);
			else if (line.find("Target", 0) == 0)
				parseTargetLine(line);
		}
		file.close();
	}
	else
	{
		std::cout << "Can't open file" << std::endl;
		buildDefaultLevel();
	}
}

void Scene::parseEmitterLine(std::string line)
{
	//Position, direction, rate, speed
	//Emitter: float float, float float, float, float 

	//Erase emitter at the beginning
	int i = line.find(" ", 0);
	if (i == std::string::npos)
		return;
	line.erase(0, i + 1);

	//Get position
	Vector position;
	position.x = popNextFloat(line);
	position.y = popNextFloat(line);

	//Get direction
	Vector direction;
	direction.x = popNextFloat(line);
	direction.y = popNextFloat(line);

	//Get rate
	float rate = popNextFloat(line);

	//Get speed
	float speed = popNextFloat(line);

	emitters.push_back(new Emitter(Transform(position), direction, rate, speed));

}

void Scene::parseTargetLine(std::string line)
{
	//Position, radius, inverseMass, velocity
	//Target: float float, float, float, float float 

	//Erase emitter at the beginning
	int i = line.find(" ", 0);
	if (i == std::string::npos)
		return;
	line.erase(0, i + 1);

	//Get position
	Vector position;
	position.x = popNextFloat(line);
	position.y = popNextFloat(line);

	//Get rate
	float radius = popNextFloat(line);

	//Get speed
	float inverseMass = popNextFloat(line);

	//Get velocity
	Vector velocity;
	velocity.x = popNextFloat(line);
	velocity.y = popNextFloat(line);

	targets.push_back(new RotatingTarget(Transform(position), radius));
}

float Scene::popNextFloat(std::string& line)
{
	float result = std::stof(line, 0);
	int i = line.find(" ");
	if (i != std::string::npos)
		line.erase(0, i + 1);
	return result;
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

	//Step through particles and update them
	for (int i = 0; i < particles.Size(); ++i)
	{
		particles[i].Update(deltaTime);
	}

	//Process Player input
	(this->*dataCollection)();
	
	//Add new particles that are created by emitters
	for (Emitter* e : emitters)
	{
		e->Update(deltaTime);
		e->AddParticle(particles);
	}

	//Delete particles that have exceeded their lifespan
	particles.RemoveElements([](const Particle& p)->bool {return p.IsAlive(); });

	//Step through targets
	for (Target* target : targets)
	{
		//Check particle collisions with target
		for (int i = 0; i < particles.Size(); ++i)
		{
			target->Collide(&particles[i]);
		}
		
		//Update target's location
		target->Update(deltaTime);
	}
}
bool Scene::Running()
{
	//Return true if there are any targets that are not clear
	for (Target* t : targets)
		if (!t->Clear())
			return true;
	return false;
}


void Scene::getMouseData()
{
	//Poll SDL mouse events
	SDL_Event mouseEvent;
	SDL_PollEvent(&mouseEvent);

	//Get mouse position
	int x, y;
	Vector mousePos;
	SDL_GetMouseState(&x, &y);
	math::PixelToNdc(mousePos, x, y);

	//Apply force to particles based on mouse position
	for (int i = 0; i < particles.Size(); ++i)
	{
		particles[i].ApplyForce(ForceFunctions::Gravity(particles[i], mousePos) * 4.0f);
	}
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

	//Resolve particle collisions with player skeletons
	player0.ResolveCollisions(particles);
	player1.ResolveCollisions(particles);
}

//Draw everything
void Scene::Render(SDL_Renderer* r)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	//Draw particles
	for (int i = 0; i < particles.Size(); ++i)
	{
		particles[i].Render(renderer);
	}

	//Draw targets
	for (Target* target : targets)
	{
		target->Render(renderer);
	}

	//Draw skeleton
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	player0.Render(renderer);
	player1.Render(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderPresent(renderer);
}


Scene::~Scene()
{
}
