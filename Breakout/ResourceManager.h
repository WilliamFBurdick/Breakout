#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>

class ResourceManager
{
public:
	~ResourceManager();
	inline static ResourceManager* Instance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new ResourceManager();
		}
		return mInstance;
	}
	bool LoadTexture(const char* path, SDL_Renderer* renderer, const char* alias);
	bool LoadFont(const char* path, int size, const char* alias);
	bool LoadSFX(const char* path, const char* alias);
	void LoadMusic(const char* path) { mMusic = Mix_LoadMUS(path); }

	SDL_Texture* GetTexture(const char* alias);
	TTF_Font* GetFont(const char* alias);
	Mix_Chunk* GetSFX(const char* alias);
	Mix_Music* GetMusic() { return mMusic; }

	SDL_Rect* GetPaddles() { return mPaddles; }
	void LoadPaddles(SDL_Texture* texture);

	SDL_Rect* GetBalls() { return mBalls; }
	void LoadBalls(SDL_Texture* texture);

	SDL_Rect* GetBricks() { return mBricks; }
	void LoadBricks(SDL_Texture* texture);

	SDL_Rect* GetHearts() { return mHearts; }
	void LoadHearts(SDL_Texture* texture);

	SDL_Rect* GetArrows() { return mArrows; }
	void LoadArrows(SDL_Texture* texture);
private:
	ResourceManager();
	static ResourceManager* mInstance;
	std::map<const char*, SDL_Texture*> mTextures;
	std::map<const char*, TTF_Font*> mFonts;
	std::map<const char*, Mix_Chunk*> mSFX;
	Mix_Music* mMusic;
	SDL_Rect* mPaddles;
	SDL_Rect* mBalls;
	SDL_Rect* mBricks;
	SDL_Rect* mHearts;
	SDL_Rect* mArrows;
};

