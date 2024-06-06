#include "PlayState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "ServeState.h"
#include "Util.h"
#include "LevelMaker.h"
#include "Game.h"

PlayState::PlayState(Game* game, Paddle* paddle, Ball* ball, std::vector<Brick*> bricks, int health, int score, int level)
	:GameState(game), mPaused(false), paddle(paddle), ball(ball), bricks(bricks), health(health), score(score), level(level)
{
	spacePressed = true;
}

PlayState::~PlayState()
{

}

void PlayState::Enter()
{

}

void PlayState::Exit()
{

}

void PlayState::Input(const Uint8* keyboard)
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
		mPaused = !mPaused;
		Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("pause"), 0);
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		spacePressed = false;
	}
}

void PlayState::Update(float deltaTime)
{
	if (!mPaused)
	{
		paddle->Update(deltaTime);
		ball->Update(deltaTime);
		if (ball->Collides(paddle->GetRect()))
		{
			ball->SetDY(-ball->GetDY());
			ball->SetY(paddle->GetRect().y - 10);

			// Tweak angle of bounce based on location hit on paddle
			// We hit the paddle on its left side while moving left
			if (ball->GetX() < paddle->GetRect().x + (paddle->GetRect().w / 2) && paddle->GetDX() < 0)
			{
				ball->SetDX(-3);
			}
			// We hit the paddle on its right side while moving right
			else if (ball->GetX() > paddle->GetRect().x + (paddle->GetRect().w / 2) && paddle->GetDX() > 0)
			{
				ball->SetDX(3);
			}

			Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("paddle-hit"), 0);
		}

		for (auto b : bricks)
		{
			if (b->InPlay() && ball->Collides(b->GetRect()))
			{
				score += (b->GetTier() + 1) * 200 + (b->GetColor() + 1) * 25;
				b->Hit();
				
				// Left edge check
				if (ball->GetX() + 2 < b->GetRect().x && ball->GetDX() > 0)
				{
					ball->SetDX(-ball->GetDX());
					ball->SetX(b->GetRect().x - 10);
				}
				// Right edge check
				else if (ball->GetX() + 6 > b->GetRect().x + b->GetRect().w && ball->GetDX() < 0)
				{
					ball->SetDX(-ball->GetDX());
					ball->SetX(b->GetRect().x + b->GetRect().w + 2);
				}
				// Top edge check
				else if (ball->GetY() < b->GetRect().y)
				{
					ball->SetDY(-ball->GetDY());
					ball->SetY(b->GetRect().y - 10);
				}
				// Bottom edge, default
				else
				{
					ball->SetDY(-ball->GetDY());
					ball->SetY(b->GetRect().y + b->GetRect().h + 2);
				}
			}
		}

		// Ball fell out of bounds
		if (ball->GetY() > VIRTUAL_HEIGHT)
		{
			health--;
			Mix_PlayChannel(-1, ResourceManager::Instance()->GetSFX("hurt"), 0);
			// Game over
			if (health <= 0)
			{
				mGame->ChangeState(new GameOverState(mGame, score));
			}
			// Lives left
			else
			{
				mGame->ChangeState(new ServeState(mGame, paddle, bricks, health, score, level));
			}
		}

		// Check victory condition
		if (CheckVictory())
		{
			mGame->ChangeState(new VictoryState(mGame, paddle, health, score, level));
		}
	}
}

void PlayState::Render(SDL_Renderer* renderer)
{
	paddle->Render(renderer);
	ball->Render(renderer);

	for (auto b : bricks)
	{
		b->Render(renderer);
	}

	Util::RenderHealth(renderer, health);
	Util::RenderScore(renderer, score);


	if (mPaused)
	{
		Util::WriteText(renderer, "large", "PAUSED", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	}
}

bool PlayState::CheckVictory()
{
	for (auto b : bricks)
	{
		if (b->InPlay())
		{
			return false;
		}
	}
	return true;
}