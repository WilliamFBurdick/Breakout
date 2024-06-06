#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameStateMachine.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	void ChangeState(GameState* newState) { mStateMachine.ChangeState(newState); }
	
private:
	void Input();
	void Update(float deltaTime);
	void Render();

private:
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	bool mRunning;

	GameStateMachine mStateMachine;
	
	const Uint8* mKeyboard;
};