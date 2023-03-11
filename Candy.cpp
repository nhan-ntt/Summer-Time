#include "Candy.h"
#include "Vari_and_Const.h"


int Candy::newItem(){
    return rand() % NumItem;
}

bool Candy::checkInit(){
    bool check = false;
    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            if (j + 2 < NumCell){
                if (items[i][j] == items[i][j + 1]
                    &&  items[i][j] == items[i][j + 2])
                {

                    items[i][j] = newItem();
                    items[i][j + 1] = newItem();
                    items[i][j + 2] = newItem();
                    check = true;
                }
            }

            if (i + 2 < NumCell){
                if (items[i][j] == items[i + 1][j]
                    &&  items[i][j] == items[i + 2][j])
                {

                    items[i][j] = newItem();
                    items[i + 1][j] = newItem();
                    items[i + 2][j] = newItem();
                    check = true;
                }
            }
        }
    }
    return check;
}

void Candy::initGame(){
    srand(time(0));
    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            items[i][j] = newItem();
        }
    }
    for(int i = 0; i < NumCell; i++){
        for(int j = 0; j < NumCell;j++)
        {
            posX[i][j] = startX + i*itemLength;
            posY[i][j] = startY + j*itemLength;
        }
    }
}

void Candy::drawGame(){

    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            int type = items[i][j];
            ItemTexture[type].Render(posX[i][j], posY[i][j], gRenderer);
        }
    }
    SDL_RenderPresent(gRenderer);

}

void Candy::play(SDL_Event* e, Button& PlayButton, LTexture gInstructionTexture, bool& QuitMenu, bool& Play,Mix_Chunk* gClick, SDL_Renderer *gRenderer){
    if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
            case SDL_MOUSEMOTION:
                PlayButton.currentSprite = BUTTON_MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                //Play = true;
                //QuitMenu = true;
                Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
                PlayButton.currentSprite = BUTTON_MOUSE_OVER;
				while (!Play){
					if (e->type == SDL_QUIT)
					{
						Play = true;
						QuitMenu = true;
						close();
					}
					gInstructionTexture.Render(0,0, gRenderer);
                    initGame();
                    drawGame();
                    SDL_RenderPresent(gRenderer);
					do{
						//gInstructionTexture.Render(0, 0, gRenderer);


						SDL_RenderPresent(gRenderer);
					}while (SDL_PollEvent(e) != 0 && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION)) ;
				}

                SDL_RenderPresent(gRenderer);
                break;
        }
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void Candy::run(){
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


                    play(&e_mouse, PlayButton, gGridTexture, Quit_Menu, Quit_Game, gClick, gRenderer);
                    HandleHelpButton(&e_mouse, gBackButton, HelpButton, BackButton, gInstructionTexture, gBackButtonTexture, gRenderer, Quit_Game, gClick );
                    HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

					if (Quit_Game == true)
					{
						return;
					}


                    //SDL_RenderPresent(gRenderer);
				}


                gMenuTexture.Render(0, 0, gRenderer);
				//gInstructionTexture.Render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

                SDL_Rect* currentClip_Play1 = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Play1, gRenderer, gHelpButtonTexture);

                SDL_Rect* currentClip_Play2 = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Play2, gRenderer, gExitButtonTexture);

				//gInstructionTexture.Render(0, 0, gRenderer);

				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();

	return;
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

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
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
	if (gClick == nullptr){
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	else{
        if (!gMenuTexture.LoadFromFile("start.png", gRenderer)){
            std::cout << "Failed to load menu image" << std::endl;
            success = false;
        }

        if (!gInstructionTexture.LoadFromFile("instruction.png", gRenderer)){
            std::cout << "Failed to load instruction image" << std::endl;
            success = false;
        }
        if (!gGridTexture.LoadFromFile("grid.png", gRenderer)){
            std::cout << "Failed to load grid image" << std::endl;
            success = false;
        }
        if (!ItemTexture[0].LoadFromFile("square.png", gRenderer))   success = false;
        if (!ItemTexture[1].LoadFromFile("heart.png", gRenderer))   success = false;
        if (!ItemTexture[2].LoadFromFile("circle.png", gRenderer))   success = false;
        if (!ItemTexture[3].LoadFromFile("diamond.png", gRenderer))   success = false;
    }
    if (!gHelpButtonTexture.LoadFromFile("help.png", gRenderer)){
        std::cout << "Failed to load help_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gHelpButton[i].x = 100 * i;
            gHelpButton[i].y = 0;
            gHelpButton[i].w = 100;
            gHelpButton[i].h = 100;
        }
    }
    if (!gPlayButtonTexture.LoadFromFile("play.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gPlayButton[i].x = 100 * i;
            gPlayButton[i].y = 0;
            gPlayButton[i].w = 100;
            gPlayButton[i].h = 100;
        }
    }
    if (!gExitButtonTexture.LoadFromFile("esc.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gExitButton[i].x = 100 * i;
            gExitButton[i].y = 0;
            gExitButton[i].w = 100;
            gExitButton[i].h = 100;
        }
    }
    if (!gBackButtonTexture.LoadFromFile("back.png", gRenderer)){
        std::cout << "Failed to load back_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gBackButton[i].x = 100 * i;
            gBackButton[i].y = 0;
            gBackButton[i].w = 100;
            gBackButton[i].h = 100;
        }
    }
	return success;
}

void close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gGridTexture.Free();

	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gBackButtonTexture.Free();
	gExitButtonTexture.Free();

	Mix_FreeChunk(gClick);

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

