#pragma once

#include "GameState.h"

class GameStartState : public GameState
{
public:
	GameStartState(class Game* game);
	~GameStartState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	int mSelected;
	bool mUpPressed, mDownPressed;
	bool mSpacePressed;
};

