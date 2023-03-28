#include "Game_Utils.h"
#include "Candy.h"

//khong co bien play, chi de bam vao va tro sang grid luon, neu muon dung cai nay thi phai sua ham Candy::play()

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
	if (HelpButton.IsInside(e, COMMON_BUTTON))
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
                        if (BackButton.IsInside(e, COMMON_BUTTON))
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
	if (ExitButton.IsInside(e, COMMON_BUTTON))
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

