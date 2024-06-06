#include "Brick.h"

Brick::Brick(int x, int y, int tier, int color, bool inPlay)
	:tier(tier), color(color), inPlay(inPlay)
{
	SDL_Rect* bricks = ResourceManager::Instance()->GetBricks();
	mSpriteRect = bricks[color * 4 + tier];
	mRect = SDL_Rect{ x, y, mSpriteRect.w, mSpriteRect.h };
}

Brick::~Brick()
{
	
}

void Brick::Init()
{

}

void Brick::Hit()
{
	if (tier > 0)
	{
		if (color == 0)
		{
			tier--;
			color = 4;
		}
		else
		{
			color--;
		}
	}
	else
	{
		if (color == 0)
		{
			inPlay = false;
		}
		else
		{
			color--;
		}
	}
	SDL_Rect* bricks = ResourceManager::Instance()->GetBricks();
	mSpriteRect = bricks[color * 4 + tier];

	Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("brick-hit-2"), 0);
}

void Brick::Render(SDL_Renderer* renderer)
{
	if (inPlay)
	{
		SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("main"), &mSpriteRect, &mRect);
	}
}