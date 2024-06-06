#include "GameOverState.h"
#include "GameStartState.h"
#include "HighScoreState.h"
#include "Game.h"
#include "Util.h"
#include "Constants.h"
#include <string>

GameOverState::GameOverState(Game* game, int score)
	:GameState(game), score(score)
{
	mSpacePressed = true;
}

GameOverState::~GameOverState()
{

}

void GameOverState::Enter()
{

}

void GameOverState::Exit()
{

}

void GameOverState::Input(const Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mGame->ChangeState(new HighScoreState(mGame, score));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}
}

void GameOverState::Update(float deltaTime)
{

}

void GameOverState::Render(SDL_Renderer* renderer)
{
	Util::WriteText(renderer, "large", "GAME OVER", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 3, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	std::string scoreText = "FINAL SCORE: " + std::to_string(score);
	Util::WriteText(renderer, "medium", scoreText.c_str(), VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, true, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
	Util::WriteText(renderer, "small", "Press SPACE to continue", VIRTUAL_WIDTH / 2, 2 * VIRTUAL_HEIGHT / 3, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
}