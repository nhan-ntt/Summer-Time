#include "Game_Utils.h"
#include "Candy.h"
//#include "Vari_and_Const.h"

void printText(int num, int POSX, int POSY, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont){
    string text = to_string(num);
    SDL_Surface* surface = TTF_RenderText_Solid(gFont, text.c_str(),textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer,surface);

    int w = 35 * text.size();
    SDL_Rect space = {POSX, POSY, w, 70};
    SDL_RenderCopy(gRenderer, texture, NULL, &space);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void HandlePlayButton(SDL_Event* e,	Button& PlayButton,	bool& menu,	bool& play,	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		menu = false;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			play = true;
			menu = false;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton,
	Button& BackButton,
	LTexture gMenuTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &quit,
	Mix_Chunk *gClick)
{
    if(e->type == SDL_QUIT){
        quit = true;
    }
	if (HelpButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			while (!ReadDone)
			{
                if (e->type == SDL_QUIT)
                {
                    ReadDone = true;
                    quit = true;
                    close();
                }
                else
                {
                    while (SDL_PollEvent(e))
                    {
                        if (BackButton.IsInside(e, SMALL_BUTTON))
                        {
                            switch (e->type)
                            {
                            case SDL_MOUSEMOTION:
                                BackButton.currentSprite = BUTTON_MOUSE_OVER;
                                break;
                            case SDL_MOUSEBUTTONDOWN:
                                BackButton.currentSprite = BUTTON_MOUSE_OVER;
                                Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
                                ReadDone = true;
                                break;
                            }
                        }

                        else
                        {
                            BackButton.currentSprite = BUTTON_MOUSE_OUT;
                        }
                        gMenuTexture.Render(0, 0, gRenderer);

                        SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
                        BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

                        SDL_RenderPresent(gRenderer);
                    }

                }
            }

        break;
        }

    }

	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void HandleExitButton(SDL_Event* e,Button& ExitButton,bool& Quit,Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:

			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
            Quit = true;
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleRestartButton(SDL_Event* e, Button& RestartButton, bool& quit, bool& Restart, Mix_Chunk* gClick){
	if (e->type == SDL_QUIT)
	{
		quit = true;
	}

	if (RestartButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			RestartButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Restart = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			RestartButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		RestartButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
