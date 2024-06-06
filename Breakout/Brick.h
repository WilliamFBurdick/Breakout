#pragma once

#include "Constants.h"
#include "ResourceManager.h"

class Brick
{
public:
	Brick(int x = 0, int y = 0, int tier = 0, int color = 1, bool inPlay = true);
	~Brick();

	void Init();
	void Hit();
	void Render(SDL_Renderer* renderer);

	int GetTier() { return tier; }
	int GetColor() { return color; }

	SDL_Rect GetRect() { return mRect; }

	bool InPlay() { return inPlay; }
private:
	SDL_Rect mRect, mSpriteRect;
	bool inPlay;
	int tier, color;
};

