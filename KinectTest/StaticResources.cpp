#include "StaticResources.h"

SDL_Surface* StaticResources::windowSurface;
SDL_Renderer* StaticResources::renderer;
std::map<std::string, SDL_Texture*> StaticResources::textures;

void StaticResources::Initialize(SDL_Renderer* r, SDL_Window* window)
{
	renderer = r;
	windowSurface = SDL_GetWindowSurface(window);

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
		return;
	}
	SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	textures[spriteName] = spriteTexture;
}

SDL_Texture* StaticResources::GetTexture(std::string name) { return textures[name]; }