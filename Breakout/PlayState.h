#pragma once

#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

#include <vector>

class PlayState : public GameState
{
public:
	PlayState(class Game* game, Paddle* paddle, Ball* ball, std::vector<Brick*> bricks, int health, int score, int level);
	~PlayState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	bool CheckVictory();
private:
	Paddle* paddle;
	Ball* ball;
	int health;
	int score;
	int level;
	std::vector<Brick*> bricks;
	bool mPaused;
	bool spacePressed;
};

