#include "PaddleSelectState.h"
#include "Game.h"
#include "ServeState.h"
#include "LevelMaker.h"

PaddleSelectState::PaddleSelectState(Game* game)
	:GameState(game)
{
	mSpacePressed = mLeftPressed = mRightPressed = true;
}

PaddleSelectState::~PaddleSelectState()
{

}

void PaddleSelectState::Enter()
{

}

void PaddleSelectState::Exit()
{

}

void PaddleSelectState::Update(float deltaTime)
{

}

void PaddleSelectState::Render(SDL_Renderer* renderer)
{
	SDL_Rect rect = ResourceManager::Instance()->GetPaddles()[selectedPaddle * 4 + 1];
	SDL_Rect posRect = SDL_Rect{
		VIRTUAL_WIDTH / 2 - rect.w / 2, VIRTUAL_HEIGHT / 2 - rect.h / 2, rect.w, rect.h
	};
	SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("main"), &rect, &posRect);
	SDL_Rect arrowRect = ResourceManager::Instance()->GetArrows()[0];
	SDL_Rect arrowPosRect = SDL_Rect{
		VIRTUAL_WIDTH / 3, VIRTUAL_HEIGHT / 2 - arrowRect.h / 2, arrowRect.w, arrowRect.h
	};
	SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("arrows"), &arrowRect, &arrowPosRect);
	arrowRect = ResourceManager::Instance()->GetArrows()[1];
	arrowPosRect.x = 2 * VIRTUAL_WIDTH / 3;
	SDL_RenderCopy(renderer, ResourceManager::Instance()->GetTexture("arrows"), &arrowRect, &arrowPosRect);
}

void PaddleSelectState::Input(const Uint8* keyboard)
{
	// Space input
	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mSpacePressed = true;

		mGame->ChangeState(new ServeState(mGame, new Paddle(
			VIRTUAL_WIDTH / 2, 5 * VIRTUAL_HEIGHT / 6, selectedPaddle
		),
			LevelMaker::CreateLevel(1), 3, 0, 1));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}
	// Arrow key input
	if (keyboard[SDL_SCANCODE_LEFT] && !mLeftPressed)
	{
		selectedPaddle++;
		if (selectedPaddle > 3)
			selectedPaddle = 0;
		mLeftPressed = true;
	}
	else if (!keyboard[SDL_SCANCODE_LEFT])
	{
		mLeftPressed = false;
	}
	if (keyboard[SDL_SCANCODE_RIGHT] && !mRightPressed)
	{
		selectedPaddle--;
		if (selectedPaddle < 0)
			selectedPaddle = 3;
		mRightPressed = true;
	}
	else if (!keyboard[SDL_SCANCODE_RIGHT])
	{
		mRightPressed = false;
	}
}