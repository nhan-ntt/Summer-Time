#ifndef CANDY_H
#define CANDY_H

#include "Game_base.h"
#include "Game_Utils.h"
#include "Button.h"
#include "LTexture.h"

#define fi first
#define se second


class Candy{
    int items[NumCell][NumCell]; //[col][row]

    int posX[NumCell][NumCell];
    int posY[NumCell][NumCell];

    int nextX[NumCell][NumCell];
    int nextY[NumCell][NumCell];

    long long score = 0;
    pair<int, int> selected[2]; //first la x, second la y, cot, hang
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

private:
    int newItem(); //ok
    bool checkInit(); //co triple khong
    int horizontal(int x, int y);   //dem so lien ke ngang chua (x, y)
    int vertical(int x, int y);     //dem so lien ke doc chua (x, y)
    bool Neighbor(int x, int y);
    bool CanSwap(int x, int y, int u, int v);
    void DropDown();
    void swapItems(int x, int y, int u, int v);
    void triple_horizontal();
    bool checkClear();
    void Stripe(int x, int y);
    void Gaturingu(int x, int y, int type);
};

#endif // CANDY_H
