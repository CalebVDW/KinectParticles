#pragma once

#include <glm\glm.hpp>

#include "Constants.h"
#include "StaticResources.h"

//This class will be an absolute mess. It has static members containing the images loaded by SDL
//Each instance will have a pointer to one of the static members and functions to render it
class Sprite
{
public:
	Sprite(std::string textureName, int width, int height);
	~Sprite();

	void Render(SDL_Renderer* renderer, Vector center);
	void Render(SDL_Renderer* renderer, Vector center, float rotation, glm::vec2 scale = glm::vec2(1.0f));

	void SetTint(glm::vec3 pTint);
	void SetAlpha(float pAlpha);
	void SetSize(int width, int height);
private:
	SDL_Texture* texture;
	int width;
	int height;
	float alpha;
	glm::vec3 tint;

	SDL_Rect calculateDrawRect(Vector center);
};

