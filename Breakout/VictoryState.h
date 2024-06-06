#pragma once

#include "GameState.h"
#include "Paddle.h"

class VictoryState : public GameState
{
public:
	VictoryState(class Game* game, Paddle* paddle, int health, int score, int level);
	~VictoryState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	Paddle* paddle;
	bool mSpacePressed;
	int score;
	int health;
	int level;
};

