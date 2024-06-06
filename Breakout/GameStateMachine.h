#pragma once
#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine(GameState* curentState = nullptr);
	~GameStateMachine();

	void ChangeState(GameState* newState);
	void Update(float deltaTime);
	void Input(const Uint8* keyboard);
	void Render(SDL_Renderer* renderer);
private:
	GameState* mCurrentState;
};

