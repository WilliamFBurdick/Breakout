#include "Util.h"
#include "Constants.h"
#include "ResourceManager.h"
#include <string>

void Util::WriteText(SDL_Renderer* renderer, const char* fontAlias, const char* text, float x, float y, bool centerAlign, SDL_Color color)
{
	TTF_Font* font = ResourceManager::Instance()->GetFont(fontAlias);
	SDL_Surface* textSurf = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);
	SDL_FreeSurface(textSurf);

	SDL_Rect rect;
	SDL_QueryTexture(textTex, NULL, NULL, &rect.w, &rect.h);
	if (centerAlign)
	{
		rect.x = x - rect.w / 2;
		rect.y = y - rect.h / 2;
	}
	else
	{
		rect.x = x;
		rect.y = y;
	}

	SDL_RenderCopy(renderer, textTex, NULL, &rect);
	SDL_DestroyTexture(textTex);
}

void Util::WriteChar(SDL_Renderer* renderer, const char* fontAlias, const char text, float x, float y, bool centerAlign, SDL_Color color)
{
	std::string textS;
	textS = (char)text;
	TTF_Font* font = ResourceManager::Instance()->GetFont(fontAlias);
	SDL_Surface* textSurf = TTF_RenderText_Solid(font, textS.c_str(), color);
	SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);
	SDL_FreeSurface(textSurf);

	SDL_Rect rect;
	SDL_QueryTexture(textTex, NULL, NULL, &rect.w, &rect.h);
	if (centerAlign)
	{
		rect.x = x - rect.w / 2;
		rect.y = y - rect.h / 2;
	}
	else
	{
		rect.x = x;
		rect.y = y;
	}

	SDL_RenderCopy(renderer, textTex, NULL, &rect);
	SDL_DestroyTexture(textTex);
}

void Util::RenderHealth(SDL_Renderer* renderer, int health)
{
	int healthX = VIRTUAL_WIDTH - 100;

	SDL_Rect* heartRects = ResourceManager::Instance()->GetHearts();
	SDL_Rect rect = SDL_Rect{
		healthX, 4, heartRects[1].w, heartRects[1].h
	};

	for (int i = 0; i < health; i++)
	{
		rect.x = healthX;
		rect.w = heartRects[1].w;
		rect.h = heartRects[1].h;
		SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("hearts"), &heartRects[0], &rect);
		healthX += 11;
	}

	for (int i = 0; i < 3 - health; i++)
	{
		rect.x = healthX;
		rect.w = heartRects[0].w;
		rect.h = heartRects[0].h;
		SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("hearts"), &heartRects[1], &rect);
		healthX += 11;
	}
}

void Util::RenderScore(SDL_Renderer* renderer, int score)
{
	std::string scoreText = "SCORE: " + std::to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(ResourceManager::Instance()->GetFont("small"), scoreText.c_str(), 
		SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });

	SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	int texWidth, texHeight;
	SDL_QueryTexture(textTex, NULL, NULL, &texWidth, &texHeight);
	SDL_Rect rect = SDL_Rect{ VIRTUAL_WIDTH - texWidth - 4, 4, texWidth, texHeight };

	SDL_RenderCopy(renderer, textTex, NULL, &rect);
	SDL_DestroyTexture(textTex);
}

SDL_Rect* Util::GenerateRects(SDL_Texture* texture, int tileWidth, int tileHeight)
{
	if (tileWidth <= 0 || tileHeight <= 0)
	{
		return nullptr;
	}
	int texWidth, texHeight;
	SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);
	int rows = texHeight / tileHeight;
	int cols = texWidth / tileWidth;
	SDL_Rect* rects = new SDL_Rect[rows * cols];
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			rects[y * rows + x] = SDL_Rect{ x * tileWidth, y * tileHeight, tileWidth, tileHeight };
		}
	}
	return rects;
}

SDL_Rect* Util::GeneratePaddleRects(SDL_Texture* texture)
{
	int x = 0;
	int y = 64;
	SDL_Rect* paddles = new SDL_Rect[4 * 4];
	for (int i = 0; i < 4; i++)
	{
		paddles[(i * 4) + 0] = SDL_Rect{ x, y, 32, 16 };
		paddles[(i * 4) + 1] = SDL_Rect{ x + 32, y, 64, 16 };
		paddles[(i * 4) + 2] = SDL_Rect{ x + 96, y, 96, 16 };
		paddles[(i * 4) + 3] = SDL_Rect{ x, y + 16, 128, 16 };
		x = 0;
		y = y + 32;
	}
	return paddles;
}

SDL_Rect* Util::GenerateBallRects(SDL_Texture* texture)
{
	// Get first row of balls
	int x = 96;
	int y = 48;
	SDL_Rect* balls = new SDL_Rect[7];
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		balls[index] = SDL_Rect{ x, y, 8, 8 };
		x = x + 8;
		index++;
	}
	// Get second row of balls
	x = 96;
	y = 56;
	for (int i = 0; i < 3; i++)
	{
		balls[index] = SDL_Rect{ x, y, 8, 8 };
		x = x + 8;
		index++;
	}

	return balls;
}

SDL_Rect* Util::GenerateBrickRects(SDL_Texture* texture)
{
	SDL_Rect* bricks = new SDL_Rect[21];
	int index = 0;
	// Grab the first 3 rows
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 6; c++)
		{
			bricks[index] = SDL_Rect{ c * 32, r * 16, 32, 16 };
			index++;
		}
	}
	// Grab last 3 bricks
	for (int c = 0; c < 3; c++)
	{
		bricks[index] = SDL_Rect{ c * 32, 48, 32, 16 };
		index++;
	}
	return bricks;
}