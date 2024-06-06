#include "ServeState.h"
#include "Game.h"
#include "PlayState.h"
#include "Util.h"

ServeState::ServeState(class Game* game, Paddle* paddle, std::vector<Brick*> bricks, int health, int score, int level)
	:GameState(game), paddle(paddle), bricks(bricks), health(health), score(score), level(level)
{
	mPaused = false;
	spacePressed = true;

	ball = new Ball(paddle->GetRect().x + paddle->GetRect().w / 2, paddle->GetRect().y - paddle->GetRect().h / 2, 1);
}

ServeState::~ServeState()
{

}

void ServeState::Enter()
{

}

void ServeState::Exit()
{

}

void ServeState::Input(const Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_LEFT])
	{
		paddle->setDX(-1);
	}
	else if (keyboard[SDL_SCANCODE_RIGHT])
	{
		paddle->setDX(1);
	}
	else
	{
		paddle->setDX(0);
	}

	if (keyboard[SDL_SCANCODE_SPACE] && !spacePressed)
	{
		spacePressed = true;
		ball->SetDY(-1);
		ball->SetDX(paddle->GetDX());
		ball->SetY(paddle->GetRect().y - paddle->GetRect().y - 2);

		mGame->ChangeState(new PlayState(mGame, paddle, ball, bricks, health, score, level));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		spacePressed = false;
	}
}

void ServeState::Update(float deltaTime)
{
	if (!mPaused)
	{
		paddle->Update(deltaTime);
		ball->SetX(paddle->GetRect().x + paddle->GetRect().w / 2);
		ball->SetY(paddle->GetRect().y - paddle->GetRect().h / 2);
	}
}

void ServeState::Render(SDL_Renderer* renderer)
{
	paddle->Render(renderer);
	ball->Render(renderer);

	for (auto b : bricks)
	{
		b->Render(renderer);
	}

	Util::RenderHealth(renderer, health);
	Util::RenderScore(renderer, score);

}