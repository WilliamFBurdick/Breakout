#pragma once

#include "ResourceManager.h"

class Util
{
public:
	static void WriteText(SDL_Renderer* renderer, const char* fontAlias, const char* text, float x, float y, bool centerAlign, SDL_Color color);
	static void WriteChar(SDL_Renderer* renderer, const char* fontAlias, const char text, float x, float y, bool centerAlign, SDL_Color color);
	static void RenderHealth(SDL_Renderer* renderer, int health);
	static void RenderScore(SDL_Renderer* renderer, int score);
	static SDL_Rect* GenerateRects(SDL_Texture* texture, int tileWidth, int tileHeight);
	static SDL_Rect* GeneratePaddleRects(SDL_Texture* texture);
	static SDL_Rect* GenerateBallRects(SDL_Texture* texture);
	static SDL_Rect* GenerateBrickRects(SDL_Texture* texture);
};

