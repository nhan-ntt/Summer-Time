#ifndef ITEM_H_
#define ITEM_H_

#include "Game_base.h"

class Item{

private:
    SDL_Rect Item[10];
    SDL_Texture* loadItem = nullptr;

public:
    ~Item();
    void DelItem();
    void loadItemTexture(std::string path, SDL_Renderer *gRenderer);
    void itemRender(int ind, int x, int y, int w, int h, SDL_Renderer* gRenderer);

};

#endif // !ITEM_H_
