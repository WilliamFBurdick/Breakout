#pragma once
#include "Constants.h"
#include "ResourceManager.h"

class Paddle
{
public:
	Paddle(int x = VIRTUAL_WIDTH / 2 - 32, int y = VIRTUAL_HEIGHT - 32, int skin = 0);
	~Paddle();
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);
	void setDX(int dx) { this->dx = dx; }
	int GetDX() { return dx; }

	SDL_Rect GetRect() { return mRect; }
private:
	SDL_Rect mRect, spriteRect;
	int x, y;
	int skin;
	int size;
	int dx;
};

