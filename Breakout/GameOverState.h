#pragma once

#include "GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState(class Game* game, int score);
	~GameOverState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	int score;
	bool mSpacePressed;
};

