#include "Game_base.h"
#include "Game_Utils.h"
#include "Button.h"
#include "LTexture.h"

const char* WINDOW_TITLE = "mo anh lennn";

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };

Mix_Chunk* gClick = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];

LTexture gMenuTexture;
LTexture gInstructionTexture;

LTexture gPlayButtonTexture;


Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);

int main(int argc, char* argv[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool Quit_Menu = false;
			bool Play_Again = false;

			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					bool Quit_Game = false;

					HandlePlayButtonnnn(&e_mouse, PlayButton, gInstructionTexture, Quit_Menu, Quit_Game, gClick, gRenderer);


					if (Quit_Game == true)
					{
						return 0;
					}
				}

				gMenuTexture.Render(0, 0, gRenderer);
				//gInstructionTexture.Render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				//gInstructionTexture.Render(0, 0, gRenderer);

				SDL_RenderPresent(gRenderer);
			}

		}
	}
	close();

	return 0;
}


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	gClick = Mix_LoadWAV("mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	else
	{
			if (!gMenuTexture.LoadFromFile("start.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("grid.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("play.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 100 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 100;
					gPlayButton[i].h = 100;
				}
			}
		}
	return success;
}

void close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();

	gPlayButtonTexture.Free();

	Mix_FreeChunk(gClick);

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

