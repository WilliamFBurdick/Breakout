#include "Game.h"
#include <cstdio>
#include <stdexcept>
#include "ResourceManager.h"

#include "Constants.h"

#include "GameStartState.h"
#include "PlayState.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL Initialization failed: %s!\n", SDL_GetError());
		throw std::exception("SDL Init Error");
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("SDL_image initialization failed: %s!\n", IMG_GetError());
		throw std::exception("SDL_image Init Error");
	}
	if (TTF_Init() < 0)
	{
		printf("SDL_ttf Initialization failed: %s!\n", TTF_GetError());
		throw std::exception("SDL_ttf Initialization Error");
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer Initialization failed: %s!\n", Mix_GetError());
		throw std::exception("SDL_mixer Initialization Error");
	}

	mWindow = SDL_CreateWindow("Breakout!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr)
	{
		printf("Failed to create SDL Window: %s!\n", SDL_GetError());
		throw std::exception("SDL Error");
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr)
	{
		printf("Failed to create SDL Renderer: %s!\n", SDL_GetError());
		throw std::exception("SDL Error");
	}

	// Set virtual resolution
	SDL_RenderSetLogicalSize(mRenderer, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

	// Load fonts
	ResourceManager::Instance()->LoadFont("assets/fonts/font.ttf", 8, "small");
	ResourceManager::Instance()->LoadFont("assets/fonts/font.ttf", 16, "medium");
	ResourceManager::Instance()->LoadFont("assets/fonts/font.ttf", 32, "large");

	// Load textures
	ResourceManager::Instance()->LoadTexture("assets/graphics/background.png", mRenderer, "background");
	ResourceManager::Instance()->LoadTexture("assets/graphics/breakout.png", mRenderer, "main");
	ResourceManager::Instance()->LoadTexture("assets/graphics/particle.png", mRenderer, "particle");
	ResourceManager::Instance()->LoadTexture("assets/graphics/hearts.png", mRenderer, "hearts");
	ResourceManager::Instance()->LoadTexture("assets/graphics/arrows.png", mRenderer, "arrows");

	// Load sounds
	ResourceManager::Instance()->LoadSFX("assets/sounds/paddle_hit.wav", "paddle-hit");
	ResourceManager::Instance()->LoadSFX("assets/sounds/brick-hit-1.wav", "brick-hit-1");
	ResourceManager::Instance()->LoadSFX("assets/sounds/brick-hit-2.wav", "brick-hit-2");
	ResourceManager::Instance()->LoadSFX("assets/sounds/confirm.wav", "confirm");
	ResourceManager::Instance()->LoadSFX("assets/sounds/high_score.wav", "high-score");
	ResourceManager::Instance()->LoadSFX("assets/sounds/hurt.wav", "hurt");
	ResourceManager::Instance()->LoadSFX("assets/sounds/no-select.wav", "no-select");
	ResourceManager::Instance()->LoadSFX("assets/sounds/pause.wav", "pause");
	ResourceManager::Instance()->LoadSFX("assets/sounds/recover.wav", "recover");
	ResourceManager::Instance()->LoadSFX("assets/sounds/score.wav", "score");
	ResourceManager::Instance()->LoadSFX("assets/sounds/select.wav", "select");
	ResourceManager::Instance()->LoadSFX("assets/sounds/victory.wav", "victory");
	ResourceManager::Instance()->LoadSFX("assets/sounds/wall_hit.wav", "wall-hit");

	ResourceManager::Instance()->LoadMusic("assets/sounds/music.wav");

	// Load paddle rects
	ResourceManager::Instance()->LoadPaddles(ResourceManager::Instance()->GetTexture("main"));
	// Load ball rects
	ResourceManager::Instance()->LoadBalls(ResourceManager::Instance()->GetTexture("main"));
	// Load brick rects
	ResourceManager::Instance()->LoadBricks(ResourceManager::Instance()->GetTexture("main"));
	// Load heart rects
	ResourceManager::Instance()->LoadHearts(ResourceManager::Instance()->GetTexture("hearts"));
	// Load arrows
	ResourceManager::Instance()->LoadArrows(ResourceManager::Instance()->GetTexture("arrows"));

	mRunning = false;
}

Game::~Game()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void Game::Run()
{
	mRunning = true;
	mStateMachine.ChangeState(new GameStartState(this));
	float lastFrame = 0.0f;
	while (mRunning)
	{
		SDL_Delay(20);
		float currentFrame = SDL_GetTicks();
		float deltaTime = (currentFrame - lastFrame) / 1000.0f;
		lastFrame = currentFrame;
		Input();
		Update(deltaTime);
		Render();
	}
}

void Game::Input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			mRunning = false;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				mRunning = false;
			}
			break;
		default:
			break;
		}

	}
	mKeyboard = SDL_GetKeyboardState(NULL);
	mStateMachine.Input(mKeyboard);
}

void Game::Update(float deltaTime)
{
	mStateMachine.Update(deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mRenderer);

	// Draw background (it's state-independent)
	SDL_Rect bgRect = {
		0, 0, VIRTUAL_WIDTH + 1, VIRTUAL_HEIGHT + 2
	};
	SDL_RenderCopy(mRenderer, ResourceManager::Instance()->GetTexture("background"), NULL, &bgRect);

	mStateMachine.Render(mRenderer);

	SDL_RenderPresent(mRenderer);
}