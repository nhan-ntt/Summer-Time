#include "Candy.h"
#include "Vari_and_Const.h"


int Candy::newItem(){
    return (rand() % NumItem);
}

bool Candy::checkInit(){
    bool check = false;
    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            if (j + 2 < NumCell){
                if (items[i][j] == items[i][j + 1] &&  items[i][j] == items[i][j + 2]){
                    items[i][j] = newItem();
                    items[i][j + 1] = newItem();
                    items[i][j + 2] = newItem();
                    check = true;
                }
            }

            if (i + 2 < NumCell){
                if (items[i][j] == items[i + 1][j] &&  items[i][j] == items[i + 2][j]){
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
    while(checkInit()) checkInit();

    for(int i = 0; i < NumCell; i++){
        for(int j = 0; j < NumCell;j++)
        {
            posX[i][j] = startX + i*itemLength;
            posY[i][j] = startY + j*itemLength;
            nextX[i][j] = posX[i][j];
            nextY[i][j] = posY[i][j];
        }
    }
    cnt_sel = 0;
    restart = false;
    quit = false;
}

int gcd(int x,int y)
{
    if (x == y || x==-y) return abs(x);
    if (x*y==0) return abs(x+y);
    return gcd(x%y,y%x);
}

void Candy::drawGame(){

    gGridTexture.Render(0, 0, gRenderer);

    bool check = false;
    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            if (posX[i][j] != nextX[i][j] || posY[i][j] != nextY[i][j]){
                check = true;
                int distanceX = nextX[i][j] - posX[i][j];
                int distanceY = nextY[i][j] - posY[i][j];
                int d = gcd(distanceX, distanceY);
                distanceX /= d;
                distanceY /= d;
                posX[i][j] += distanceX * itemSpeed;
                posY[i][j] += distanceY * itemSpeed;
            }
        }
    }

    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            int type = items[i][j];
            if (type != BLANK)
                ItemTexture[type].Render_size(posX[i][j], posY[i][j], itemLength, itemLength, gRenderer);
            else
                DisTexture.Render_size(posX[i][j], posY[i][j], itemLength, itemLength, gRenderer);

            //ItemTexture[type].Render(posX[i][j], posY[i][j], gRenderer, &clip[i][j]);
        }
    }

    if(cnt_sel == 1){
        //ChooseTexture.Render_size(posX[selected[0].fi], posY[selected[0].se], itemLength, itemLength, gRenderer);
        int x = posX[selected[0].fi][selected[0].se];
        int y = posY[selected[0].fi][selected[0].se];
        ChooseTexture.Render_size(x, y, itemLength, itemLength, gRenderer);
    }

    SDL_RenderPresent(gRenderer);

    if(check)   drawGame();
}

string conv(int i){
    if (i == -1)    return "BLANK";
    if (i == 0)    return "SQUARE";
    if (i == 1)    return "HEART";
    if (i == 2)    return "CIRCLE";
    if (i == 3)    return "DIAMOND";
    if (i == 4)    return "QUAD_hori";
    if (i == 5)    return "QUAD_vert";
    if (i == 6)    return "QUIN";
    else return "haizzzzzzzz";
}

void Candy::updateTouch(int mouseX, int mouseY){
    int row = (mouseY - startY) / itemLength;
    int col = (mouseX - startX) / itemLength;

    cout << row << ' ' << col << " ********** "<< conv(items[col][row]) << endl;
    if (row < 0 || col < 0 || row >= NumCell || col >= NumCell)
        return;
    if (cnt_sel != 1){
        selected[0].fi = col;
        selected[0].se = row;
        cnt_sel = 1;
    }
    else{
        if ((col == selected[0].fi - 1 && row == selected[0].se) ||
            (col == selected[0].fi + 1 && row == selected[0].se) ||
            (col == selected[0].fi && row == selected[0].se + 1) ||
            (col == selected[0].fi && row == selected[0].se - 1))
        {
            selected[1].fi = col;
            selected[1].se = row;
            cnt_sel = 2;
        }
        else cnt_sel = 0;
    }
}

void Candy::swapItems(int x, int y, int u, int v){
    nextX[x][y] = posX[u][v];
    nextY[x][y] = posY[u][v];
    nextX[u][v] = posX[x][y];
    nextY[u][v] = posY[x][y];

    drawGame();
    swap(posX[x][y], posX[u][v]);
    swap(posY[x][y], posY[u][v]);

    nextX[x][y] = posX[x][y];
    nextY[x][y] = posY[x][y];
    nextX[u][v] = posX[u][v];
    nextY[u][v] = posY[u][v];

    swap(items[x][y], items[u][v]);
}

void Candy::DropDown()
{
    //drop
    for (int col = 0; col < NumCell; col++){
        int blank = NumCell - 1;
        while (blank >= 0){
            while (items[col][blank] != -1 && blank >= 0)  blank--;
            int nah = blank;
            while (items[col][nah] == -1 && nah >= 0)  nah--;
            if(nah < 0)   break;
            swap(items[col][nah], items[col][blank]);
            //now blank = nah, nah = blank
            posX[col][blank] = posX[col][nah];
            posY[col][blank] = posY[col][nah];
        }
    }

    //generate
    for (int col = NumCell - 1; col >= 0; col--){
        int rowo = 0;
        for (int row = NumCell - 1; row >= 0; row--){
            if(items[col][row] == BLANK){
                posX[col][row] = startX + col * itemLength;

                if (rowo == 0)  rowo = itemLength;
                else rowo += itemLength;

                posY[col][row] = startY - rowo;

                items[col][row] = newItem();
            }
        }
    }

    drawGame();
}

bool Candy::checkClear()
{
    int cnt, row, col;
    bool can = false;

    for(col = 0; col < NumCell; col++)
    {
        cnt = 1;
        for(row = 1; row <= NumCell; row++)
            if (items[col][row] >= BLANK && items[col][row] == items[col][row - 1]) cnt++;
            else
            {
                if (cnt > 2)
                {
                    can = true;
                    for(int i = row - 1; i >= row - cnt; i--) items[col][i] = -1;
                    if (cnt == 5) items[col][row - cnt] = QUINTUPLE;
                    if (cnt == 4) items[col][row - cnt] = QUAD_HORI;
                }
                cnt = 1;
            }
    }

    for(row = 0; row < NumCell; row++)
    {
        cnt = 1;
        for(col = 1; col <= NumCell; col++)
            if (items[col][row] >= BLANK && items[col][row] == items[col - 1][row]) cnt++;
            else
            {
                if (cnt > 2)
                {
                    can = true;
                    for(int i = col - 1; i >= col - cnt; i--) items[i][row] = -1;
                    if (cnt == 5) items[col - cnt][row] = QUINTUPLE;
                    if (cnt == 4) items[col - cnt][row] = QUAD_VERT;
                }
                cnt = 1;
            }
    }

    return can;
}

int Candy::horizontal(int x, int y){
    int y_left = y - 1;
    int y_right = y + 1;
    if (items[x][y] == BLANK)   return 0;
    while (y_left >= 0 && items[x][y_left] == items[x][y])  y_left--;
    while (y_right < NumCell && items[x][y_right] == items[x][y])  y_right++;

    if (y_right - y_left - 1 >= 3){
        for (int i = y_left + 1; i < y_right; i++){
            //if (i != y)
                //items[x][i] = BLANK;
        }
    }
    return y_right - y_left - 1;
}

int Candy::vertical(int x, int y){
    int x_up = x - 1;
    int x_down = x + 1;
    if (items[x][y] == BLANK)   return 0;
    while (x_up >= 0 && items[x_up][y] == items[x][y])  x_up--;
    while (x_down < NumCell && items[x_down][y] == items[x][y])  x_down++;

    if (x_down - x_up - 1 >= 3){
        for (int i = x_up + 1; i < x_down; i++){
            //if (i != x)
                //items[i][y] = BLANK;
        }
    }
    return x_down - x_up - 1;
}

bool Candy::Neighbor(int x, int y){
    int hori = horizontal(x, y);
    int vert = vertical(x, y);
    //if (hori != 0 || vert != 0) items[x][y] = BLANK;
    return (hori >= 3 ||  vert >= 3);
}

bool Candy::CanSwap(int x, int y, int u, int v){
    return Neighbor(x, y) || Neighbor(u, v);
}

void Candy::Stripe(int x, int y){
    if (items[x][y] == QUAD_HORI){
        for (int i = 0; i < NumCell; i++){
            items[x][i] = BLANK;
        }
    }
    else if (items[x][y] == QUAD_VERT){
        for (int i = 0; i < NumCell; i++){
            items[i][y] = BLANK;
        }
    }
}

void Candy::Gaturingu(int x, int y, int type){
    for (int i = 0; i < NumCell; i++)
        for (int j = 0; j < NumCell; j++)
            if(items[i][j] == type)
                items[i][j] = BLANK;
    items[x][y] = BLANK;
}

void Candy::updateBoard(){
    while(checkClear())
    {
        //eatItems();
        //print();
        drawGame();
        Sleep(timeSleep);
        DropDown();
    }
}


void Candy::updateGame(){
    int x = selected[0].fi, y = selected[0].se;
    int u = selected[1].fi, v = selected[1].se;

    if (cnt_sel == 2){
        cnt_sel = 0;
        if (items[x][y] == QUINTUPLE && items[u][v] != QUINTUPLE){
            Gaturingu(x, y, items[u][v]);
            updateBoard();
        }
        else if (items[x][y] != QUINTUPLE && items[u][v] == QUINTUPLE){
            Gaturingu(u, v, items[x][y]);
            updateBoard();
        }
        else{
            swapItems(x, y, u, v);

            if(!CanSwap(x, y, u, v)){
                swapItems(x, y, u, v);
            }
            else updateBoard();
        }

    }
    else if(cnt_sel == 1 && (items[x][y] == QUAD_HORI || items[x][y] == QUAD_VERT)){
        cnt_sel = 0;
        Stripe(x, y);
        updateBoard();
    }
}

void Candy::run(){
    const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

    if (init() && loadMedia())
    {
        frameStart = SDL_GetTicks();

        while (menu)
        {
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0)
            {
                if (e_mouse.type == SDL_QUIT){
                    menu = false;
                    quit = true;
                }

                HandlePlayButton(&e_mouse, PlayButton, menu, play, gClick);
                HandleHelpButton(&e_mouse, gBackButton, HelpButton, BackButton, gInstructionTexture, gBackButtonTexture, gRenderer, quit, gClick );
                HandleExitButton(&e_mouse, ExitButton, quit, gClick);

                if (quit == true)   return;

            }

            gMenuTexture.Render(0, 0, gRenderer);

            SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
            PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

            SDL_Rect* currentClip_Play1 = &gHelpButton[HelpButton.currentSprite];
            HelpButton.Render(currentClip_Play1, gRenderer, gHelpButtonTexture);

            SDL_Rect* currentClip_Play2 = &gExitButton[ExitButton.currentSprite];
            ExitButton.Render(currentClip_Play2, gRenderer, gExitButtonTexture);
            SDL_RenderPresent(gRenderer);
        }

        initGame();

        while (play)
        {

            int mouseX, mouseY;
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0)
            {
                if (e_mouse.type == SDL_QUIT){
                    play = false;
                    quit = true;
                }

                if (e_mouse.type == SDL_MOUSEBUTTONDOWN){
                    cout << mouseX << ' ' << mouseY << endl;

                    SDL_GetMouseState(&mouseX, &mouseY);
                    updateTouch(mouseX, mouseY);

                }
                updateGame();
                drawGame();

                frameTime = SDL_GetTicks() - frameStart;
                if (frameDelay > frameTime)
                {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
            if (quit == true && play == false)   return;

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

        if (!ItemTexture[4].LoadFromFile("quad_hori.png", gRenderer))   success = false;

        if (!ItemTexture[5].LoadFromFile("quad_vert.png", gRenderer))   success = false;

        if (!ItemTexture[6].LoadFromFile("quin.png", gRenderer))   success = false;

        if (!ChooseTexture.LoadFromFile("meo.png", gRenderer))   success = false;

        if (!DisTexture.LoadFromFile("kaguu.png", gRenderer))   success = false;

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

