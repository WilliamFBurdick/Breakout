#include "Ball.h"

Ball::Ball(int x, int y, int skin)
	:x(x), y(y), skin(skin), dx(0), dy(0)
{
	SDL_Rect* balls = ResourceManager::Instance()->GetBalls();
	mSpriteRect = balls[skin];
	mRect = SDL_Rect{ x, y, mSpriteRect.w, mSpriteRect.h };
}

Ball::~Ball()
{}

void Ball::Update(float deltaTime)
{
	x = x + dx;
	y = y + dy;

	if (x <= 0 || x >= VIRTUAL_WIDTH - mSpriteRect.w)
	{
		Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("wall-hit"), 0);
		dx = -dx;
	}
	if (y <= 0)
	{
		Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("wall-hit"), 0);
		dy = -dy;
	}
}

void Ball::Render(SDL_Renderer* renderer)
{
	mRect.x = x;
	mRect.y = y;
	SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("main"), &mSpriteRect, &mRect);
}

bool Ball::Collides(SDL_Rect other)
{
	if (mRect.x + mRect.w >= other.x && mRect.x <= other.x + other.w &&
		mRect.y + mRect.h >= other.y && mRect.y <= other.y + other.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}