#include "GameStartState.h"
#include "Game.h"
#include "Constants.h"
#include "Util.h"
#include "LevelMaker.h"
#include "ServeState.h"
#include "HighScoreState.h"
#include "PaddleSelectState.h"

GameStartState::GameStartState(Game* game)
	:GameState(game), mSelected(1), mUpPressed(false), mDownPressed(false), mSpacePressed(true)
{

}

GameStartState::~GameStartState()
{
	
}

void GameStartState::Enter()
{

}

void GameStartState::Exit()
{

}

void GameStartState::Update(float deltaTime)
{

}

void GameStartState::Render(SDL_Renderer* renderer)
{
	Util::WriteText(renderer, "large", "BREAKOUT!", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 3, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	if (mSelected == 1)
	{
		Util::WriteText(renderer, "medium", "START", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 70, true, SDL_Color{ 0x64, 0xFF, 0xFF, 0xFF });
		Util::WriteText(renderer, "medium", "HIGH SCORES", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 90, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	}
	else
	{
		Util::WriteText(renderer, "medium", "START", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 70, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
		Util::WriteText(renderer, "medium", "HIGH SCORES", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2 + 90, true, SDL_Color{ 0x64, 0xFF, 0xFF, 0xFF });
	}
}

void GameStartState::Input(const Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_UP] && !mUpPressed)
	{
		mUpPressed = true;
		mSelected = (mSelected == 1) ? 2 : 1;
		Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("paddle-hit"), 0);
	}
	else if (!keyboard[SDL_SCANCODE_UP])
	{
		mUpPressed = false;
	}
	if (keyboard[SDL_SCANCODE_DOWN] && !mDownPressed)
	{
		mDownPressed = true;
		mSelected = (mSelected == 1) ? 2 : 1;
		Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("paddle-hit"), 0);
	}
	else if (!keyboard[SDL_SCANCODE_DOWN])
	{
		mDownPressed = false;
	}

	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mSpacePressed = true;
		if (mSelected == 1)
		{
			mGame->ChangeState(new PaddleSelectState(mGame));
		}
		else if (mSelected == 2)
		{
			// Change to high score state
			mGame->ChangeState(new HighScoreState(mGame, 0));
		}
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}

}