#include "EnterHighScoreState.h"
#include "Game.h"
#include <algorithm>
#include "Util.h"
#include "Constants.h"

EnterHighScoreState::EnterHighScoreState(class Game* game, std::vector<HighScoreEntry> highscores, int score)
	:GameState(game), highscores(highscores), score(score)
{
	chars = new char[3] {
		65, 65, 65
		};
	highlightedChar = 0;

	mSpacePressed = mLeftPressed = mRightPressed = mUpPressed = mDownPressed = true;
}

EnterHighScoreState::~EnterHighScoreState()
{}

void EnterHighScoreState::Enter()
{

}

void EnterHighScoreState::Exit()
{

}

void EnterHighScoreState::Input(const Uint8* keyboard)
{
	// Handle Space input
	if (keyboard[SDL_SCANCODE_SPACE] && !mSpacePressed)
	{
		mSpacePressed = true;
		// Write new highscores to file
		HighScoreEntry entry;
		std::string char1, char2, char3;
		char1 = (char)chars[0];
		char2 = (char)chars[1];
		char3 = (char)chars[2];
		std::string name = char1 + char2 + char3;
		entry.name = name;
		entry.score = score;
		highscores.push_back(entry);

		// Sort scores
		std::sort(highscores.begin(), highscores.end(), [](const HighScoreEntry& lhs, const HighScoreEntry& rhs)
			{
				return lhs.score > rhs.score;
			});
		// Remove lowest score
		highscores.pop_back();

		// Save scores to file
		std::ofstream oFile("high-scores.txt");
		for (auto s : highscores)
		{
			oFile << s.name << ":" << s.score << '\n';
		}
		oFile.close();

		// Change state
		mGame->ChangeState(new HighScoreState(mGame, 0));
	}
	else if (!keyboard[SDL_SCANCODE_SPACE])
	{
		mSpacePressed = false;
	}
	// Handle right input
	if (keyboard[SDL_SCANCODE_RIGHT] && !mRightPressed)
	{
		mRightPressed = true;
		// Move to next character
		highlightedChar++;
		if (highlightedChar > 2)
			highlightedChar = 0;
	}
	else if (!keyboard[SDL_SCANCODE_RIGHT])
	{
		mRightPressed = false;
	}
	// Handle left input
	if (keyboard[SDL_SCANCODE_LEFT] && !mLeftPressed)
	{
		mLeftPressed = true;
		// Move to previous character
		highlightedChar--;
		if (highlightedChar < 0)
			highlightedChar = 2;
	}
	else if (!keyboard[SDL_SCANCODE_LEFT])
	{
		mLeftPressed = false;
	}
	// Handle up input
	if (keyboard[SDL_SCANCODE_UP] && !mUpPressed)
	{
		mUpPressed = true;
		chars[highlightedChar]++;
		if (chars[highlightedChar] > 90)
			chars[highlightedChar] = 65;
	}
	else if (!keyboard[SDL_SCANCODE_UP])
	{
		mUpPressed = false;
	}
	// Handle down input
	if (keyboard[SDL_SCANCODE_DOWN] && !mDownPressed)
	{
		mDownPressed = true;
		chars[highlightedChar]--;
		if (chars[highlightedChar] < 65)
			chars[highlightedChar] = 90;
	}
	else if (!keyboard[SDL_SCANCODE_DOWN])
	{
		mDownPressed = false;
	}

}

void EnterHighScoreState::Update(float deltaTime)
{

}

void EnterHighScoreState::Render(SDL_Renderer* renderer)
{
	std::string text = "Your score: " + std::to_string(score);
	Util::WriteText(renderer, "medium", text.c_str(), VIRTUAL_WIDTH / 2, 30, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });

	SDL_Color highlightColor = SDL_Color{ 0x64, 0xFF, 0xFF, 0xFF };
	SDL_Color plainColor = SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF };

	if (highlightedChar == 0)
	{
		Util::WriteChar(renderer, "large", chars[0], VIRTUAL_WIDTH / 2 - 28, VIRTUAL_HEIGHT / 2, true, highlightColor);
	}
	else
	{
		Util::WriteChar(renderer, "large", chars[0], VIRTUAL_WIDTH / 2 - 28, VIRTUAL_HEIGHT / 2, true, plainColor);
	}
	if (highlightedChar == 1)
	{
		Util::WriteChar(renderer, "large", chars[1], VIRTUAL_WIDTH / 2 - 6, VIRTUAL_HEIGHT / 2, true, highlightColor);
	}
	else
	{
		Util::WriteChar(renderer, "large", chars[1], VIRTUAL_WIDTH / 2 - 6, VIRTUAL_HEIGHT / 2, true, plainColor);
	}
	if (highlightedChar == 2)
	{
		Util::WriteChar(renderer, "large", chars[2], VIRTUAL_WIDTH / 2 + 16, VIRTUAL_HEIGHT / 2, true, highlightColor);
	}
	else
	{
		Util::WriteChar(renderer, "large", chars[2], VIRTUAL_WIDTH / 2 + 16, VIRTUAL_HEIGHT / 2, true, plainColor);
	}
	Util::WriteText(renderer, "small", "Press SPACE to confirm!", VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT - 18, true, SDL_Color{ 0xFF, 0xFF, 0xFF, 0xFF });
}