#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState* currentState)
	:mCurrentState(currentState)
{

}

GameStateMachine::~GameStateMachine()
{
	delete mCurrentState;
	mCurrentState = nullptr;
}

void GameStateMachine::ChangeState(GameState* newState)
{
	if (mCurrentState != nullptr)
	{
		mCurrentState->Exit();
	}
	mCurrentState = newState;
	if (mCurrentState != nullptr)
	{
		mCurrentState->Enter();
	}
}

void GameStateMachine::Update(float deltaTime)
{
	if (mCurrentState != nullptr)
	{
		mCurrentState->Update(deltaTime);
	}
}

void GameStateMachine::Render(SDL_Renderer* renderer)
{
	if (mCurrentState != nullptr)
	{
		mCurrentState->Render(renderer);
	}
}

void GameStateMachine::Input(const Uint8* keyboard)
{
	if (mCurrentState != nullptr)
	{
		mCurrentState->Input(keyboard);
	}
}