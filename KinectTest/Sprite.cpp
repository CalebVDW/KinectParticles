#include "Sprite.h"



Sprite::Sprite(std::string textureName, int width, int height)
	:texture{ StaticResources::GetTexture(textureName) }, width{ width }, height{ height }
{
}

void Sprite::Render(SDL_Renderer* renderer, Vector center)
{
	//Calculate center point in screen coordinates
	SDL_Rect destRect = calculateDrawRect(center);

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void Sprite::Render(SDL_Renderer* renderer, Vector center, float rotation, glm::vec2 scale)
{
	SDL_Rect destRect = calculateDrawRect(center);
	SDL_Point center;
	math::NdcToPixel(center.x, center.y, center);
	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, rotation, )
}

SDL_Rect Sprite::calculateDrawRect(Vector center)
{
	//Convert from NDC to screen coords
	SDL_Rect drawRect;
	math::NdcToPixel(drawRect.x, drawRect.y, center);
	drawRect.w = width;
	drawRect.h = height;

	//Shift the rectangle because SDL draws from the top left corner
	drawRect.x -= width / 2;
	drawRect.y -= height / 2;
	return drawRect;
}

Sprite::~Sprite()
{
}
