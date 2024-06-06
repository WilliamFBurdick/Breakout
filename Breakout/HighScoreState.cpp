#include "HighScoreState.h"
#include "GameStartState.h"
#include "EnterHighScoreState.h"

#include "Game.h"
#include <algorithm>
#include "Util.h"
#include "Constants.h"

HighScoreState::HighScoreState(Game* game, int score)
	:GameState(game), score(score)
{
	mSpacePressed = true;
}

HighScoreState::~HighScoreState()
{

}

void HighScoreState::Enter()
{
	std::ifstream iFile("high-scores.txt");
	if (!iFile.is_open())
	{
		// No file exists, populate with default data
		for (int i = 0; i < 10; i++)
		{
			HighScoreEntry entry;
			entry.name = "WFB";
			entry.score = (i + 1) * 1000;
			highScores.push_back(entry);
		}
	}
	else
	{
		while (!iFile.eof())
		{
			HighScoreEntry entry;
			std::string line;
			std::getline(iFile, line, ':');
			if (!line.empty())
			{
				entry.name = line;
				std::getline(iFile, line, '\n');
				entry.score = stoi(line);

				highScores.push_back(entry);
			}
		}
		iFile.close();
	}

	// Sort scores
	std::sort(highScores.begin(), highScores.end(), [](const HighScoreEntry& lhs, const HighScoreEntry& rhs)
		{
			return lhs.score > rhs.score;
		});

	if (score > highScores[highScores.size() - 1].score)
	{
		mGame->ChangeState(new EnterHighScoreState(mGame, highScores, score));
	}
}

void HighScoreState::Exit()
{
	std::ofstream oFile("high-scores.txt");
	for (auto s : highScores)
	{
		oFile << s.name << ":" << s.score << '\n';
	}
	oFile.close();
}

void HighScoreState::Input(const Uint8* keyboard)
{
	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mSpacePressed = true;
		mGame->ChangeState(new GameStartState(mGame));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}
}

void HighScoreState::Update(float deltaTime)
{}

void HighScoreState::Render(SDL_Renderer* renderer)
{
	Util::WriteText(renderer, "large", "HIGH SCORES", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 6, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
	int y = VIRTUAL_HEIGHT / 6 + 20;
	for (auto s : highScores)
	{
		y += 15;
		std::string text = s.name + " : " + std::to_string(s.score);
		Util::WriteText(renderer, "medium", text.c_str(), VIRTUAL_WIDTH / 2, y, true, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
	}
	y += 20;
	Util::WriteText(renderer, "small", "Press SPACE to return to menu", VIRTUAL_WIDTH / 2, y, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
}