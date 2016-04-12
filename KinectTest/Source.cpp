//Caleb Van Der Werf
//Kinect particle project

#include <iostream>
#include <SDL.h>

#include "Scene.h"

//TODO/////////////////////////////////////////////////////////////////////////
//Determine inheritance hierarchy for this project
//I am going to have some foresight here and design to expand easily
//Set up image importing
//Make a generalized animation handling system
///////////////////////////////////////////////////////////////////////////////


//Globals because I'm a lazy bastard
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

//Initializes SDL only
bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize window
	*window = SDL_CreateWindow("StackOverflow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);

	return true;
}

//I have decided that all coordinates should be in NDC like they are in OpenGL
//This could have implications for rectangular windows so I will be using square windows for now

//All times will be in seconds for simplicity
//Colors will be passed as floats/vecs until render time//Values 0-1.0f
int main(int argc, char** argv){
	std::cout << "Hello World!";

	//Check if there is a sensor
	int sensorCount = 0;
	NuiGetSensorCount(&sensorCount);
	if (sensorCount < 1)
	{
		std::cout << "No sensor detected";
		return -1;
	}

	//Step through all Kinect sensors
	HRESULT hr;
	INuiSensor* tempSensor = NULL;
	INuiSensor* m_sensor = NULL;
	for (int i = 0; i < sensorCount; ++i)
	{
		//Attempt to create the sensor pointer
		hr = NuiCreateSensorByIndex(i, &tempSensor);
		if (FAILED(hr))
			continue;

		//Check status of the current sensor
		hr = tempSensor->NuiStatus();
		if (S_OK == hr)
		{
			m_sensor = tempSensor;
			break;
		}
		tempSensor->Release();
	}

	HANDLE skeletonReady = nullptr;
	if (m_sensor != NULL)
	{
		hr = m_sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
		if (SUCCEEDED(hr))
		{
			skeletonReady = CreateEventW(NULL, TRUE, FALSE, NULL);
			hr = m_sensor->NuiSkeletonTrackingEnable(skeletonReady, 0);
		}
	}

	if (m_sensor == NULL || FAILED(hr))
	{
		std::cout << "No Kinect Found";
		return E_FAIL;
	}

	//Initialize SDL
	init(&window, &renderer);

	//Initialize scene
	Scene myScene;

	//NEW GAME LOOP HERE///////////////////////////////////////////////////////////////////////////

	//Kinect event polling stuff
	HANDLE events[1];
	std::cout << "Arrived at Game Loop" << std::endl;
	while (true)
	{
		//Wait indefinitely until a skeleton becomes available 
		events[0] = skeletonReady;
		MsgWaitForMultipleObjects(1, events, FALSE, INFINITE, QS_ALLINPUT);

		if (m_sensor == NULL)
			return -1;

		if (WAIT_OBJECT_0 == WaitForSingleObject(skeletonReady, 0))
		{
			NUI_SKELETON_FRAME myFrame = { 0 };
			HRESULT r = m_sensor->NuiSkeletonGetNextFrame(0, &myFrame);
			if (FAILED(r))
			{
				std::cout << "Could not load skeleton" << std::endl;
				continue;
			}

			//Smooth skeleton data
			m_sensor->NuiTransformSmooth(&myFrame, NULL);

			myScene.update(&myFrame);
			myScene.render(renderer);
		}
	}
	//END GAME LOOP////////////////////////////////////////////////////////////////////////////////

	return 0;
}
/*#include <iostream>
#include <thread>
#include <chrono>

#include <SDL.h>

#include <Windows.h>
#include <NuiApi.h>

using namespace std;

bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize window
	*window = SDL_CreateWindow("StackOverflow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 800, SDL_WINDOW_SHOWN);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	return true;
}


int main(int argc, char** argv){
	cout << "Hello World!";

	//Check if there is a sensor
	int count;
	NuiGetSensorCount(&count);
	if (count < 1)
		return -1;

	//Create an interface for the sensor
	INuiSensor* sensor;
	NuiCreateSensorByIndex(0, &sensor);

	//Create event
	HANDLE myEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		TEXT("MyEvent")
		);

	//I don't know what this is
	sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
	sensor->NuiSkeletonTrackingEnable(NULL, NULL);

	//Enable skeleton tracking
	HRESULT hr = NuiSkeletonTrackingEnable(myEvent, 0);
	NUI_SKELETON_FRAME myFrame;

	//Initialize SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	init(&window, &renderer);
	
	while (true)
	{
		//Get skeleton data
		NuiSkeletonGetNextFrame(1000, &myFrame);

		//Get the first tracked skeleton
		cout << myFrame.SkeletonData[0].SkeletonPositions[0].x << ", " << myFrame.SkeletonData[0].SkeletonPositions[0].y << endl;

		//Step through all bones
		for (int i = 0; i < 10; i++)
		{
			//Get joint positions
			int x1, y1, x2, y2;
			x1 = int(100.0f * myFrame.SkeletonData[0].SkeletonPositions[i].x);
			y1 = int(100.0f * myFrame.SkeletonData[0].SkeletonPositions[i].y);
			x2 = int(100.0f * myFrame.SkeletonData[0].SkeletonPositions[i + 1].x);
			y2 = int(100.0f * myFrame.SkeletonData[0].SkeletonPositions[i + 1].y);

			//Draw debug lines
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		}

		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	return 0;
	}*/