#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include "Game_base.h"

class LTexture
{
public:
	LTexture();

	~LTexture();

	void Free();

	bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	bool LoadFromFile(std::string path, SDL_Renderer *gRenderer);

	void LoadItemsFromFile(std::string path, SDL_Renderer *gRenderer);

	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);

	void Render_size(int x, int y, int w, int h, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
	void Render_size_type(int type, int x, int y, int w, int h, SDL_Renderer* gRenderer);

	void Render_Text(int size, int POSX, int POSY, stringstream& text, const int& num,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

	int GetWidth();

	int GetHeight();
	SDL_Rect rItem[NumItem];

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif // !LTEXTURE_H_
