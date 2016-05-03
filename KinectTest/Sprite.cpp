#include "Sprite.h"



Sprite::Sprite(std::string textureName, int width, int height)
	:texture{ StaticResources::GetTexture(textureName) }, width{ width }, height{ height }
{
	alpha = 1.0f;
	tint = glm::vec3(255.0f);
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
	destRect.w = int(scale.x * float(destRect.w));
	destRect.h = int(scale.y * float(destRect.h));
	SDL_Point centerPoint;
	math::NdcToPixel(centerPoint.x, centerPoint.y, center);
	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, rotation, &centerPoint, SDL_FLIP_NONE);
}

void Sprite::SetAlpha(float pAlpha) 
{ 
	alpha = pAlpha;
	SDL_SetTextureColorMod(texture, Uint8(alpha * tint.x), Uint8(alpha * tint.y), Uint8(alpha * tint.z));
}
void Sprite::SetTint(glm::vec3 pTint) 
{
	tint = pTint * 255.0f;
	SDL_SetTextureColorMod(texture, Uint8(alpha * tint.x), Uint8(alpha * tint.y), Uint8(alpha * tint.z));
}
void Sprite::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}
//PRIVATE FUNCTIONS////////////////////////////////////////////////////////////
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
