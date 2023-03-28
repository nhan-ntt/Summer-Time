#ifndef CANDY_H
#define CANDY_H

#include "Game_base.h"
#include "Game_Utils.h"
#include "Button.h"
#include "LTexture.h"

#define fi first
#define se second

const int NumCell = 5;
const int NumItem = 4;
const int itemLength = 100;
const int startX = 75;
const int startY = 50;
const int itemSpeed = 10;

class Candy{
    int items[NumCell][NumCell];

    int posX[NumCell][NumCell];
    int posY[NumCell][NumCell];

    int nextX[NumCell][NumCell];
    int nextY[NumCell][NumCell];

    long long score = 0;
    pair<int, int> selected[2]; //first la x, second la y
    int cnt_sel = 0;

    bool quit = false;
    bool menu = true;
    bool play = false;
    bool restart = false;

public:
    void initGame(); // khoi tao toa do vi tri
    void run();
    void drawGame(); //render board
    void updateGame(); //tam
    void updateBoard();
    void updateTouch(int mouseX, int mouseY); //update selected
    //void play(SDL_Event* e, Button& PlayButton, LTexture gInstructionTexture, bool& QuitMenu, bool& Play,Mix_Chunk* gClick, SDL_Renderer *gRenderer);

private:
    int newItem(); //ok
    bool checkInit(); //co triple khong
    void generateItems();
    void swapItems(int x, int y, int u, int v);

};

#endif // CANDY_H
