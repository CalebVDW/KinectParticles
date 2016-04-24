#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <iostream>
#include <string>

class StaticResources {
public:
	static SDL_Surface* windowSurface;
	static SDL_Renderer* renderer;
	static void Initialize(SDL_Renderer* r);
	static void LoadPNG(std::string path, std::string spriteName);
	static SDL_Texture* GetTexture(std::string name);

private:
	static std::map<std::string, SDL_Texture*> textures;
};

