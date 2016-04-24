#include "StaticResources.h"

SDL_Surface* StaticResources::windowSurface;
SDL_Renderer* StaticResources::renderer;
std::map<std::string, SDL_Texture*> StaticResources::textures;

void StaticResources::Initialize(SDL_Renderer* r)
{
	renderer = r;
	//Initialize SDL Image
	bool success;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags)&imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}
}

void StaticResources::LoadPNG(std::string path, std::string spriteName)
{
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Image not loaded" << std::endl;
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, windowSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
	textures[spriteName] = spriteTexture;
}

SDL_Texture* StaticResources::GetTexture(std::string name) { return textures[name]; }