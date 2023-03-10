#ifndef CANDY_H
#define CANDY_H

#include "Game_base.h"

const int NumCell = 8;
const int NumItem = 2;

class Candy{
    int items[NumCell][NumCell];
    int posX[NumCell][NumCell];
    int posY[NumCell][NumCell];
    int eleX[NumCell][NumCell];
    int eleY[NumCell][NumCell];

    long long score = 0;

    bool quit = false;

public:
    void initGame();
    void run();
    void drawGame();
    void updateGame();

private:
    int newItem();
    bool checkInit();
    void generateItems();
};

#endif // CANDY_H
