#include "LTexture.h"

LTexture::LTexture()
{
	mTexture = nullptr;

	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	Free();
}

void LTexture::Free()
{
    //SDL_DestroyTexture(mTexture);
	if (mTexture != nullptr)
	{
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::LoadFromRenderedText(std::string textureText,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

bool LTexture::LoadFromFile(std::string path, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		//LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			//LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			mWidth = tmpSurface->w;
			mHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	mTexture = tmpTexture;

	return mTexture != nullptr;
}

void LTexture::LoadItemsFromFile(std::string path, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		//LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			//LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			mWidth = tmpSurface->w;
			mHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	mTexture = tmpTexture;
//
//	rItem[SQUARE] = {0, 0, 545, 475};
//	rItem[CIRCLE] = {1445, 0, 555, 525};
//	rItem[HEART] = {1345, 1410, 550, 590};
//	rItem[DIAMOND] = {0, 1405, 500, 550};
}

void LTexture::Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{

	SDL_Rect renderSpace = { x, y, mWidth, mHeight};

	if (clip != nullptr)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}

void LTexture::Render_size(int x, int y, int w, int h, SDL_Renderer* gRenderer, SDL_Rect* clip){
	SDL_Rect renderSpace = { x, y, w, h};

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}

void LTexture::Render_size_type(int type, int x, int y, int w, int h, SDL_Renderer* gRenderer){
    SDL_Rect renderSpace = { x, y, w, h};

	SDL_RenderCopy(gRenderer, mTexture, &rItem[type], &renderSpace);
}

void LTexture::Render_Text(int size, int POSX, int POSY, stringstream& text, const int& num, TTF_Font *gFont, SDL_Color textColor, SDL_Renderer* gRenderer){
    SDL_DestroyTexture(mTexture);
	if (mTexture != nullptr)
	{
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
    text.str("");
    text << num;
    if (LoadFromRenderedText(text.str().c_str(), gFont, textColor, gRenderer)){
        Render(POSX + (size - GetWidth()) / 2, POSY, gRenderer);
    }
}

int LTexture::GetWidth()
{
	return mWidth;
}

int LTexture::GetHeight()
{
	return mHeight;
}

