#include "Candy.h"
#include "Vari_and_Const.h"


int Candy::newItem(){
    return (rand() % (NumItem + 0));
}

bool Candy::checkInit(){
    bool check = false;
    for (int i = 0; i < NumCOL; i++){
        for (int j = 0; j < NumROW; j++){
            if (j + 2 < NumROW){
                if (items[i][j] == items[i][j + 1] &&  items[i][j] == items[i][j + 2]){
                    items[i][j] = newItem();
                    items[i][j + 1] = newItem();
                    items[i][j + 2] = newItem();
                    check = true;
                }
            }

            if (i + 2 < NumCOL){
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
    for (int i = 0; i < NumCOL; i++){
        for (int j = 0; j < NumROW; j++){
            items[i][j] = newItem();
        }
    }
    while(checkInit()) checkInit();

    for(int i = 0; i < NumCOL; i++){
        for(int j = 0; j < NumROW;j++)
        {
            posX[i][j] = startX + i*itemLength;
            posY[i][j] = startY + j*itemLength;
            nextX[i][j] = posX[i][j];
            nextY[i][j] = posY[i][j];
        }
    }
    cnt_sel = 0;
    moves = moveAllowed[level];
    target = maxScore[level];
    score = 0;
    Pscore = {0, 0};
    restart = false;
    quit = false;
    y = startY - 540;
    endgame = false;

}

int gcd(int x,int y){
    //if (x == y || x==-y) return abs(x);
    if (x*y==0) return abs(x+y);
    //return gcd(x%y,y%x);
}

stringstream ScoreText, MoveText;

void Candy::drawGame(){

    SDL_Delay(10);

    gGridTexture.Render_size(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

    bool check = false;
    for (int i = 0; i < NumCOL; i++){
        for (int j = 0; j < NumROW; j++){
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

    for (int i = 0; i < NumCOL; i++){
        for (int j = 0; j < NumROW; j++){
            int type = items[i][j];
            if (type != BLANK)
                //nhan.Render_size_type(type, posX[i][j], posY[i][j], itemLength, itemLength, gRenderer);
                //ItemTexture[type].Render_size(posX[i][j], posY[i][j], itemLength, itemLength, gRenderer);
                ItemTexture[type].Render(posX[i][j], posY[i][j],gRenderer);
            else{
                DisTexture.Render(posX[i][j], posY[i][j], gRenderer);
                //SDL_Delay(10);
            }
        }
    }

    if(cnt_sel == 1){
        int x = posX[selected[0].fi][selected[0].se];
        int y = posY[selected[0].fi][selected[0].se];
        ChooseTexture.Render(x, y, gRenderer);
    }

    //printText(score, SCORE_POSX, SCORE_POSY, textColor, gRenderer, gFont);
    //printText(moves, MOVE_POSX, MOVE_POSY, textColor, gRenderer, gFont);
    ScoreTexture.Render_Text(120, SCORE_POSX, SCORE_POSY, sscore, score, gFont, textColor, gRenderer);
    MoveTexture.Render_Text(70, MOVE_POSX, MOVE_POSY, smove, moves, gFont, textColor, gRenderer);

    TargetTexture.Render_Text(120, TAR_POSX, TAR_POSY, smove, target, gFont, textColor, gRenderer);

    //printText(target, TAR_POSX, TAR_POSY, textColor, gRenderer, gFont);

    if(endgame){
        if (y < startY){
            if (lose){
                LoseTexture.Render(startX, y += itemSpeed * 2, gRenderer);
                //if (y == startY)    LoseTexture.Render(startX, startY, gRenderer);
            }
            else{
                VictoryTexture.Render(startX, y += itemSpeed * 2, gRenderer);
                //if (y == startY)    LoseTexture.Render(startX, startY, gRenderer);
            }
        }


        SDL_Rect* currentClip_Restart = &gRestartButton[RestartButton.currentSprite];
        RestartButton.Render(currentClip_Restart, gRenderer, gRestartButtonTexture);

        check = false;
    }

    if (y == startY){
        if (lose)   LoseTexture.Render(startX, startY, gRenderer);
        else        VictoryTexture.Render(startX, startY, gRenderer);
    }


    SDL_Rect* currentClip_Play2 = &gRestartButton[RestartButton.currentSprite];
    RestartButton.Render(currentClip_Play2, gRenderer, gRestartButtonTexture);

    SDL_Rect* currentClip_Home = &gHomeButton[HomeButton.currentSprite];
    HomeButton.Render(currentClip_Home, gRenderer, gHomeButtonTexture);

    SDL_RenderPresent(gRenderer);

    if(check)   drawGame();
}

string conv(int i){
    if (i == -1)    return "BLANK";
    if (i == 0)    return "COCONUT";
    if (i == 1)    return "PINEAPPLE";
    if (i == 2)    return "WATERMELON";
    if (i == 3)    return "ORANGE";
    if (i == 4)    return "QUAD_hori";
    if (i == 5)    return "QUAD_vert";
    if (i == 6)    return "QUIN";
    else return "haizzzzzzzz";
}

void Candy::updateTouch(int mouseX, int mouseY){
    int row = (mouseY - startY) / itemLength;
    int col = (mouseX - startX) / itemLength;

    cout << row << ' ' << col << " ********** "<< conv(items[col][row]) << endl;
    if (row < 0 || col < 0 || row >= NumROW || col >= NumCOL)
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

void Candy::DropDown(){
    //drop

    for (int col = 0; col < NumCOL; col++){
        int blank = NumROW - 1;
        while (blank >= 0){
            while (items[col][blank] != BLANK && blank >= 0)  blank--;
            int nah = blank;
            while (items[col][nah] == BLANK && nah >= 0)  nah--;
            if(nah < 0)   break;
            swap(items[col][nah], items[col][blank]);
            //now blank = nah, nah = blank
            posX[col][blank] = posX[col][nah];
            posY[col][blank] = posY[col][nah];

        }
    }

    //generate
    for (int col = NumCOL - 1; col >= 0; col--){
        int rowo = 0;
        for (int row = NumROW - 1; row >= 0; row--){
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

bool Candy::checkClear(int &score){
    int cnt, row, col;
    bool can = false;

    SDL_Delay(5);
    for(col = 0; col <= NumCOL; col++)
    {
        cnt = 1;
        for(row = 1; row <= NumROW; row++)
            if (row < NumROW && items[col][row] < QUAD_VERT && items[col][row] > BLANK && items[col][row] == items[col][row - 1]) cnt++;
            else
            {
                if (cnt > 2)
                {
                    can = true;
                    for(int i = row - 1; i >= row - cnt; i--){
                        items[col][i] = BLANK;
                        DisTexture.Render(posX[col][i], posY[col][i], gRenderer);
                        //SDL_Delay(5);
                        SDL_RenderPresent(gRenderer);
                    }
                    if (cnt == 5) items[col][row - cnt] = QUINTUPLE;
                    if (cnt == 4) items[col][row - cnt] = QUAD_HORI;
                    if (cnt == 4 || cnt == 5)   score++;
                }

                cnt = 1;
            }
    }

    for(row = 0; row <= NumROW; row++)
    {
        cnt = 1;
        for(col = 1; col <= NumCOL; col++)
            if (col < NumCOL && items[col][row] < QUAD_VERT && items[col][row] > BLANK && items[col][row] == items[col - 1][row]) cnt++;
            else
            {
                if (cnt > 2)
                {
                    can = true;
                    for(int i = col - 1; i >= col - cnt; i--){
                        items[i][row] = BLANK;
                        DisTexture.Render(posX[i][row], posY[i][row], gRenderer);
                        //SDL_Delay(5);
                        SDL_RenderPresent(gRenderer);
                    }
                    if (cnt == 5) items[col - cnt][row] = QUINTUPLE;
                    if (cnt == 4) items[col - cnt][row] = QUAD_VERT;
                    if (cnt == 4 || cnt == 5)   score++;

                }
                cnt = 1;
            }
    }
    return can;
}

int Candy::horizontal(int x, int y){
    int y_left = y - 1;
    int y_right = y + 1;
    if (items[x][y] == BLANK || items[x][y] >= QUAD_VERT)   return 0;
    while (y_left >= 0 && items[x][y_left] == items[x][y])  y_left--;
    while (y_right < NumROW && items[x][y_right] == items[x][y])  y_right++;

    return y_right - y_left - 1;
}

int Candy::vertical(int x, int y){
    int x_up = x - 1;
    int x_down = x + 1;
    if (items[x][y] == BLANK || items[x][y] >= QUAD_VERT)   return 0;
    while (x_up >= 0 && items[x_up][y] == items[x][y])  x_up--;
    while (x_down < NumCOL && items[x_down][y] == items[x][y])  x_down++;

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
        for (int i = 0; i < NumROW; i++){
            if (items[x][i] == QUINTUPLE)
                continue;
            else if (items[x][i] == QUAD_VERT){
                Stripe(x, i);
                SDL_Delay(5);
            }
            else{
                items[x][i] = BLANK;
                DisTexture.Render(posX[x][i], posY[x][i], gRenderer);
                SDL_Delay(5);
            }
            SDL_RenderPresent(gRenderer);
        }
    }


    else if (items[x][y] == QUAD_VERT){
        for (int i = 0; i < NumCOL; i++){
            if (items[i][y] == QUINTUPLE)
                continue;
            else if (items[i][y] == QUAD_HORI)
                Stripe(i, y);
            else{
                items[i][y] = BLANK;
                DisTexture.Render(posX[i][y], posY[i][y], gRenderer);
                SDL_Delay(5);
            }
            SDL_RenderPresent(gRenderer);

        }
    }

}

void Candy::Gaturingu(int x, int y, int type){
    if (type == QUINTUPLE){
        for (int i = 0; i < NumCOL; i++){
            for (int j = 0; j < NumROW; j++){
                items[i][j] = BLANK;
                DisTexture.Render(posX[i][j], posY[i][j], gRenderer);
                SDL_Delay(5);
                SDL_RenderPresent(gRenderer);
            }
        }
    }


    for (int i = 0; i < NumCOL; i++)
        for (int j = 0; j < NumROW; j++){
            if (type == QUAD_HORI || type == QUAD_VERT){
                if (items[i][j] == QUAD_HORI || items[i][j] == QUAD_VERT)
                    Stripe(i, j);
            }
            else if(items[i][j] == type){
                items[i][j] = BLANK;
                DisTexture.Render(posX[i][j], posY[i][j], gRenderer);
                SDL_Delay(5);
                SDL_RenderPresent(gRenderer);
            }

        }
    items[x][y] = BLANK;
}

void Candy::updateScore(int *score, pair <int, int>& Pscore){
    for (int i = 0; i < NumCOL; i++)
        for (int j = 0; j < NumROW; j++)
            if (items[i][j] == BLANK){
                (*score)++;
            }
    (Pscore.se) = (*score);
}

void Candy::updateMoves(int* moves){
    if (cnt_sel == 2){
        --(*moves);
    }
    //else if (cnt_sel != 0) --(*moves);
}

void Candy::updateBoard(){
    while (true){
        updateScore(&score, Pscore);
        updateMoves(&moves);
        drawGame();
        Sleep(timeSleep);
        DropDown();
        SDL_Delay(5);
        if(!checkClear(score)) break;
    }
}


void Candy::updateGame(int &moves){
    int x = selected[0].fi, y = selected[0].se;
    int u = selected[1].fi, v = selected[1].se;

    if (cnt_sel == 2){
        cnt_sel = 0;
        if (items[x][y] == QUINTUPLE && items[u][v] == QUINTUPLE){
            Gaturingu(x, y, items[u][v]);
            updateBoard();
        }
        if (items[x][y] == QUINTUPLE && items[u][v] != QUINTUPLE){
            Gaturingu(x, y, items[u][v]);
            updateBoard();
        }
        else{
            swapItems(x, y, u, v);

            if(!CanSwap(x, y, u, v)){
                swapItems(x, y, u, v);
                moves++;
            }
            updateBoard();
        }
    }
    else if(cnt_sel == 1 && (items[x][y] == QUAD_HORI || items[x][y] == QUAD_VERT)){
        cnt_sel = 0;
        Stripe(x, y);
        moves--;

        updateBoard();
    }
}

void Candy::GamePlay(){
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    frameStart = SDL_GetTicks();

        initGame();

        if (menu)     Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);

        while (menu)
        {
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0)
            {
                if (e_mouse.type == SDL_QUIT){
                    menu = false;
                    quit = true;
                }

                HandleLevelButton(&e_mouse, PlayButton, menu, chooselevel, gClick);
                HandleHelpButton(&e_mouse, gBackButton, HelpButton, BackButton, gInstructionTexture, gBackButtonTexture, gRenderer, quit, gClick );
                HandleExitButton(&e_mouse, ExitButton, quit, gClick);

                if (quit == true)   return;
            }

            gMenuTexture.Render_size(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

            SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
            PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

            SDL_Rect* currentClip_Play1 = &gHelpButton[HelpButton.currentSprite];
            HelpButton.Render(currentClip_Play1, gRenderer, gHelpButtonTexture);

            SDL_Rect* currentClip_Play2 = &gExitButton[ExitButton.currentSprite];
            ExitButton.Render(currentClip_Play2, gRenderer, gExitButtonTexture);

            SDL_RenderPresent(gRenderer);
            SDL_RenderClear(gRenderer);

        }

        while (chooselevel)
        {
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0)
            {
                if (e_mouse.type == SDL_QUIT){
                    menu = false;
                    quit = true;
                }
                HandleEASYButton(&e_mouse, EASYButton, chooselevel, play, gClick, level);
                HandleMEDIUMButton(&e_mouse, MEDIUMButton, chooselevel, play, gClick, level);
                HandleHARDButton(&e_mouse, HARDButton, chooselevel, play, gClick, level);

                if (quit == true)   return;

            }

            gLevelTexture.Render_size(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

            SDL_Rect* currentClip_EASY = &gEASYButton[EASYButton.currentSprite];
            EASYButton.Render(currentClip_EASY, gRenderer, gEASYButtonTexture);

            SDL_Rect* currentClip_MEDIUM = &gMEDIUMButton[MEDIUMButton.currentSprite];
            MEDIUMButton.Render(currentClip_MEDIUM, gRenderer, gMEDIUMButtonTexture);

            SDL_Rect* currentClip_HARD = &gHARDButton[HARDButton.currentSprite];
            HARDButton.Render(currentClip_HARD, gRenderer, gHARDButtonTexture);


            SDL_RenderPresent(gRenderer);
            SDL_RenderClear(gRenderer);
        }

        initGame();

        if(play)    Mix_PlayMusic(gMusic, IS_REPEATITIVE);

        while (play)
        {
            int mouseX, mouseY;
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0)
            {
                if (quit == true)   return;

                if (e_mouse.type == SDL_QUIT){
                    quit = true;
                }

                HandleRestartButton(&e_mouse, RestartButton, quit, restart, gClick);
                HandleHomeButton(&e_mouse, HomeButton, menu, play, gClick);
                SDL_RenderPresent(gRenderer);

                if (menu){
                        GamePlay();
                        return;
                }

                if (restart){
                    initGame();
                    endgame = false;
                    play = true;
                }


                if (play){
                    if (e_mouse.type == SDL_MOUSEBUTTONDOWN){
                        cout << mouseX << ' ' << mouseY << endl;

                        SDL_GetMouseState(&mouseX, &mouseY);
                        updateTouch(mouseX, mouseY);
                        updateMoves(&moves);
                    }
                }

                updateGame(moves);
                drawGame();

                frameTime = SDL_GetTicks() - frameStart;
                if (frameDelay > frameTime)
                {
                    SDL_Delay(frameDelay - frameTime);
                }
            }
            if (endgame)
                drawGame();


            if (play){
                if (moves == 0){
                    endgame = true;
                    if (score >= maxScore[level])  lose = false;
                    else                    lose = true;
                }
            }
        }
}

void Candy::run(){

    if (init() && loadMedia())
    {
        if (!quit)  GamePlay();
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

    gClick = Mix_LoadWAV("audio/mouse_click.wav");
    gMusic = Mix_LoadMUS("audio/summertime.wav");
    gMenuMusic = Mix_LoadMUS("audio/menu_audio.wav");

    if (gClick == nullptr){
        LogError("Failed to load mouse click sound", MIX_ERROR);
        success = false;
    }
    if (gMusic == nullptr){
        LogError("Failed to load chichi sound", MIX_ERROR);
        success = false;
    }
    gFont = TTF_OpenFont("resources/setofont.ttf", 70);
    if (gFont == NULL)
    {
        LogError("Failed to load font", MIX_ERROR);
        success = false;
    }
    else{
        if (!gMenuTexture.LoadFromFile("image/start.png", gRenderer)){
            std::cout << "Failed to load menu image" << std::endl;
            success = false;
        }

        if (!gInstructionTexture.LoadFromFile("image/instruction.png", gRenderer)){
            std::cout << "Failed to load instruction image" << std::endl;
            success = false;
        }
        if (!gGridTexture.LoadFromFile("image/grid.png", gRenderer)){
            std::cout << "Failed to load grid image" << std::endl;
            success = false;
        }
        if (!gLevelTexture.LoadFromFile("image/level.png", gRenderer)){
            std::cout << "Failed to load menu image" << std::endl;
            success = false;
        }
        nhan.LoadItemsFromFile("image/candee1.png", gRenderer);

        if (!ItemTexture[COCONUT].LoadFromFile("image/coconut.png", gRenderer))   success = false;

        if (!ItemTexture[PINEAPPLE].LoadFromFile("image/pineapple.png", gRenderer))   success = false;

        if (!ItemTexture[WATERMELON].LoadFromFile("image/watermelon.png", gRenderer))   success = false;

        if (!ItemTexture[ORANGE].LoadFromFile("image/orange.png", gRenderer))   success = false;

        if (!ItemTexture[4].LoadFromFile("image/quad_hori.png", gRenderer))   success = false;

        if (!ItemTexture[5].LoadFromFile("image/quad_vert.png", gRenderer))   success = false;

        if (!ItemTexture[6].LoadFromFile("image/quin.png", gRenderer))   success = false;

        if (!ChooseTexture.LoadFromFile("image/choose.png", gRenderer))   success = false;

        if (!HoriTexture.LoadFromFile("image/hori_stripe.png", gRenderer))   success = false;

        if (!VertTexture.LoadFromFile("image/vert_stripe.png", gRenderer))   success = false;

        if (!DisTexture.LoadFromFile("image/dis.png", gRenderer))   success = false;

        if (!VictoryTexture.LoadFromFile("image/victory.png", gRenderer))   success = false;

        if (!LoseTexture.LoadFromFile("image/lose.png", gRenderer))   success = false;

    }
    if (!gHelpButtonTexture.LoadFromFile("image/help.png", gRenderer)){
        std::cout << "Failed to load help_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gHelpButton[i].x = 90 * i;
            gHelpButton[i].y = 0;
            gHelpButton[i].w = 90;
            gHelpButton[i].h = 85;
        }
    }
    if (!gPlayButtonTexture.LoadFromFile("image/play.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gPlayButton[i].x = 180 * i;
            gPlayButton[i].y = 0;
            gPlayButton[i].w = 180;
            gPlayButton[i].h = 95;
        }
    }
    if (!gExitButtonTexture.LoadFromFile("image/esc.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gExitButton[i].x = 90 * i;
            gExitButton[i].y = 0;
            gExitButton[i].w = 90;
            gExitButton[i].h = 85;
        }
    }

    if (!gHomeButtonTexture.LoadFromFile("image/home.png", gRenderer)){
        std::cout << "Failed to load home_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gHomeButton[i].x = 90 * i;
            gHomeButton[i].y = 0;
            gHomeButton[i].w = 90;
            gHomeButton[i].h = 85;
        }
    }

    if (!gBackButtonTexture.LoadFromFile("image/back.png", gRenderer)){
        std::cout << "Failed to load back_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gBackButton[i].x = 90 * i;
            gBackButton[i].y = 0;
            gBackButton[i].w = 90;
            gBackButton[i].h = 85;
        }
    }

    if (!gRestartButtonTexture.LoadFromFile("image/restart.png", gRenderer)){
        std::cout << "Failed to load restart_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gRestartButton[i].x = 90 * i;
            gRestartButton[i].y = 0;
            gRestartButton[i].w = 90;
            gRestartButton[i].h = 85;
        }
    }

    if (!gEASYButtonTexture.LoadFromFile("image/easy.png", gRenderer)){
        std::cout << "Failed to load help_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gEASYButton[i].x = 180 * i;
            gEASYButton[i].y = 0;
            gEASYButton[i].w = 180;
            gEASYButton[i].h = 95;
        }
    }
    if (!gMEDIUMButtonTexture.LoadFromFile("image/medium.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gMEDIUMButton[i].x = 180 * i;
            gMEDIUMButton[i].y = 0;
            gMEDIUMButton[i].w = 180;
            gMEDIUMButton[i].h = 95;
        }
    }
    if (!gHARDButtonTexture.LoadFromFile("image/hard.png", gRenderer)){
        std::cout << "Failed to load play_button image" << std::endl;
        success = false;
    }
    else{
        for (int i = 0; i < BUTTON_TOTAL; ++i){
            gHARDButton[i].x = 180 * i;
            gHARDButton[i].y = 0;
            gHARDButton[i].w = 180;
            gHARDButton[i].h = 95;
        }
    }

    return success;
}


void close()
{
    gMenuTexture.Free();
    gInstructionTexture.Free();
    gGridTexture.Free();
    gLevelTexture.Free();

    ChooseTexture.Free();
    HoriTexture.Free();
    VertTexture.Free();
    DisTexture.Free();

    ScoreTexture.Free();
    MoveTexture.Free();

    VictoryTexture.Free();
    LoseTexture.Free();
    nhan.Free();

    gPlayButtonTexture.Free();
    gHelpButtonTexture.Free();
    gBackButtonTexture.Free();
    gExitButtonTexture.Free();
    gHomeButtonTexture.Free();
    gRestartButtonTexture.Free();

    Mix_FreeChunk(gClick);
    Mix_FreeMusic(gMusic);
    Mix_FreeMusic(gMenuMusic);

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    gClick = nullptr;
    gMusic = nullptr;
    gMenuMusic = nullptr;

    TTF_CloseFont(gFont);
    gFont = NULL;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

