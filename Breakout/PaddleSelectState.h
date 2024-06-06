#pragma once

#include "GameState.h"
#include "Paddle.h"

class PaddleSelectState : public GameState
{
public:
	PaddleSelectState(class Game* game);
	~PaddleSelectState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	int selectedPaddle;
	bool mSpacePressed, mLeftPressed, mRightPressed;
};

