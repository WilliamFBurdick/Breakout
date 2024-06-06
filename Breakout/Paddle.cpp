#include "Paddle.h"

Paddle::Paddle(int x, int y, int skin)
	:x(x), y(y), dx(0), skin(skin)
{
	size = 1;
	SDL_Rect* paddles = ResourceManager::Instance()->GetPaddles();
	spriteRect = paddles[skin * 4 + size];
	mRect = SDL_Rect{
		x, y, spriteRect.w, spriteRect.h
	};
}

Paddle::~Paddle()
{

}

void Paddle::Update(float deltaTime)
{
	x = x + dx * PADDLE_SPEED;
	if (x < 0) x = 0;
	if (x > VIRTUAL_WIDTH - spriteRect.w) x = VIRTUAL_WIDTH - spriteRect.w;
}

void Paddle::Render(SDL_Renderer* renderer)
{
	mRect.x = x;
	mRect.y = y;
	SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("main"), &spriteRect, &mRect);
}

