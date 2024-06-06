#pragma once

#include "GameState.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include <vector>

class ServeState : public GameState
{
public:
	ServeState(class Game* game, Paddle* paddle, std::vector<Brick*> bricks, int health, int score, int level);
	~ServeState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
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

