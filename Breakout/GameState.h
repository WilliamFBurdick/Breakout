#pragma once
#include <SDL.h>
#include "ResourceManager.h"
class GameState
{
public:
	GameState(class Game* owner)
		:mGame(owner) {}
	virtual void Enter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Input(const Uint8* keyboard) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void Exit() = 0;
protected:
	class Game* mGame;
};