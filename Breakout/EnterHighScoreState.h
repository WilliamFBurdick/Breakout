#pragma once

#include "GameState.h"
#include "HighScoreState.h"

class EnterHighScoreState : public GameState
{
public:
	EnterHighScoreState(class Game* game, std::vector<HighScoreEntry> highscores, int score);
	~EnterHighScoreState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	char* chars;
	int highlightedChar;
	int score;
	std::vector<HighScoreEntry> highscores;
	bool mSpacePressed, mLeftPressed, mRightPressed, mUpPressed, mDownPressed;
};

