#ifndef CANDY_H
#define CANDY_H

#include "Game_base.h"
#include "Game_Utils.h"
#include "Button.h"
#include "LTexture.h"


const int NumCell = 5;
const int NumItem = 4;
const int itemLength = 100;
const int startX = 75;
const int startY = 50;

class Candy{
    int items[NumCell][NumCell];
    int posX[NumCell][NumCell];
    int posY[NumCell][NumCell];

    long long score = 0;

    bool quit = false;

public:
    void initGame();
    void run();
    void drawGame();
    void updateGame();
    void play(SDL_Event* e, Button& PlayButton, LTexture gInstructionTexture, bool& QuitMenu, bool& Play,Mix_Chunk* gClick, SDL_Renderer *gRenderer);


private:
    int newItem();
    bool checkInit();
    void generateItems();
};

#endif // CANDY_H
