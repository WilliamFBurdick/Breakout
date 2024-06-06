#include "ResourceManager.h"
#include "Util.h"

ResourceManager* ResourceManager::mInstance = nullptr;

ResourceManager::~ResourceManager()
{
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
		mTextures.erase(i.first);
	}
}

ResourceManager::ResourceManager()
{
	mInstance = nullptr;
	mTextures = std::map<const char*, SDL_Texture*>();
	mFonts = std::map<const char*, TTF_Font*>();
}

bool ResourceManager::LoadTexture(const char* path, SDL_Renderer* renderer, const char* alias)
{
	if (mTextures.find(alias) != mTextures.end())
	{
		return false;
	}
	SDL_Surface* tempSurface = IMG_Load(path);
	if (tempSurface == nullptr)
	{
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	mTextures.emplace(alias, texture);
	return true;
}

bool ResourceManager::LoadFont(const char* path, int size, const char* alias)
{
	if (mFonts.find(alias) != mFonts.end())
	{
		return false;
	}
	TTF_Font* font = TTF_OpenFont(path, size);
	mFonts.emplace(alias, font);
	return true;
}

bool ResourceManager::LoadSFX(const char* path, const char* alias)
{
	if (mSFX.find(alias) != mSFX.end())
	{
		return false;
	}
	Mix_Chunk* sfx = Mix_LoadWAV(path);
	if (sfx == nullptr)
	{
		return false;
	}
	mSFX.emplace(alias, sfx);
	return true;
}

SDL_Texture* ResourceManager::GetTexture(const char* alias)
{
	auto it = mTextures.find(alias);
	if (it != mTextures.end())
	{
		return mTextures[alias];
	}
	else
	{
		return nullptr;
	}
}

TTF_Font* ResourceManager::GetFont(const char* alias)
{
	auto it = mFonts.find(alias);
	if (it != mFonts.end())
	{
		return mFonts[alias];
	}
	else
	{
		return nullptr;
	}
}

Mix_Chunk* ResourceManager::GetSFX(const char* alias)
{
	auto it = mSFX.find(alias);
	if (it != mSFX.end())
	{
		return mSFX[alias];
	}
	else
	{
		return nullptr;
	}
}

void ResourceManager::LoadPaddles(SDL_Texture* texture)
{
	mPaddles = Util::GeneratePaddleRects(texture);
}

void ResourceManager::LoadBalls(SDL_Texture* texture)
{
	mBalls = Util::GenerateBallRects(texture);
}

void ResourceManager::LoadBricks(SDL_Texture* texture)
{
	mBricks = Util::GenerateBrickRects(texture);
}

void ResourceManager::LoadHearts(SDL_Texture* texture)
{
	mHearts = Util::GenerateRects(texture, 10, 9);
}

void ResourceManager::LoadArrows(SDL_Texture* texture)
{
	mArrows = Util::GenerateRects(texture, 24, 24);
}