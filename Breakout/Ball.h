#pragma once

#include "Constants.h"
#include "ResourceManager.h"

class Ball
{
public:
	Ball(int x = VIRTUAL_WIDTH / 2, int y = VIRTUAL_HEIGHT / 2, int skin = 0);
	~Ball();

	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }

	int GetY() { return y; }
	int GetX() { return x; }

	void SetDX(int dx) { this->dx = dx; }
	void SetDY(int dy) { this->dy = dy; }

	int GetDY() { return dy; }
	int GetDX() { return dx; }

	bool Collides(SDL_Rect other);

private:
	SDL_Rect mSpriteRect, mRect;
	int x, y;
	int skin;
	int dx, dy;
};

