//public:
//    void initGame();
//    void run();
//    void drawGame();
//    void updateTouch(int mouseX, int mouseY);
//    void updateGame();
//
//private:
//    int newItem();
//    bool checkInit();
//    void generateItems();

#include "Candy.h"

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

    while (checkInit())    checkInit();

    for (int i = 0; i < NumCell; i++){
        for (int j = 0; j < NumCell; j++){
            eleX[i][j] =
        }
    }
}
