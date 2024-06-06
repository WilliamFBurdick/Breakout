#pragma once

#include "GameState.h"
#include <fstream>
#include <vector>
#include <string>

struct HighScoreEntry {
	std::string name;
	int score;
};

class HighScoreState : public GameState
{
public:
	HighScoreState(class Game* game, int score);
	~HighScoreState();
	void Enter() override;
	void Input(const Uint8* keyboard) override;
	void Exit() override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
	int score;
	std::vector<HighScoreEntry> highScores;
	bool mSpacePressed;
};

