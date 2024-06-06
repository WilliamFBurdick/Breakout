#include "VictoryState.h"
#include "ServeState.h"
#include "Game.h"
#include "Util.h"
#include "Constants.h"
#include "LevelMaker.h"

#include <string>

VictoryState::VictoryState(Game* game, Paddle* paddle, int health, int score, int level)
	:GameState(game), paddle(paddle), health(health), score(score), level(level)
{
	mSpacePressed = true;
}

VictoryState::~VictoryState()
{
	
}

void VictoryState::Enter() {}
void VictoryState::Exit() {}

void VictoryState::Input(const Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mSpacePressed = true;
		mGame->ChangeState(new ServeState(mGame, paddle, LevelMaker::CreateLevel(level + 1), health, score, level + 1));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}
}

void VictoryState::Update(float deltaTime) {}

void VictoryState::Render(SDL_Renderer* renderer)
{
	Util::RenderHealth(renderer, health);
	Util::RenderScore(renderer, score);
	std::string levelText = "Level " + std::to_string(level) + " Complete!";
	std::string nextLevelText = "Press SPACE to go to Level " + std::to_string(level + 1);
	Util::WriteText(renderer, "medium", levelText.c_str(), VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	Util::WriteText(renderer, "large", "VICTORY!", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 3, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	Util::WriteText(renderer, "small", nextLevelText.c_str(), VIRTUAL_WIDTH / 2, 2 * VIRTUAL_HEIGHT / 3, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
}