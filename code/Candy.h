#ifndef CANDY_H
#define CANDY_H

#include "Game_base.h"
#include "Game_Utils.h"
#include "Button.h"
#include "LTexture.h"
#include "Item.h"

#define fi first
#define se second

class Candy{
    int items[NumCOL][NumROW]; //[col][row]

    int posX[NumCOL][NumROW];
    int posY[NumCOL][NumROW];

    int nextX[NumCOL][NumROW];
    int nextY[NumCOL][NumROW];

    stringstream sscore, smove;

    int y = startY - 540;

    int score = 0;
    pair<int, int> Pscore;
    pair<int, int> selected[2]; //first la x, second la y, cot, hang
    int cnt_sel = 0;
    int moves = moveAllowed;
    int target = maxScore;

    bool quit = false;
    bool menu = true;
    bool play = false;
    bool restart = false;
    bool lose = false;
    bool endgame = false;

public:
    void initGame(); // khoi tao toa do vi tri
    void run();
    void drawGame(); //render board
    void updateGame(int &moves); //tam
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
    bool checkClear(int &score);
    void Stripe(int x, int y);
    void Gaturingu(int x, int y, int type);
    //void updateScore(int *score);
    void updateScore(int *score, pair <int, int>& Pscore);
    void updateMoves(int *moves);
};

#endif // CANDY_H
