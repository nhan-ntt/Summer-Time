#include "Item.h"

Item::~Item(){}

void Item::DelItem(){
    SDL_DestroyTexture(loadItem);
    loadItem = nullptr;
}

void Item::loadItemTexture(std::string path, SDL_Renderer *gRenderer){
    DelItem();
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

    loadItem = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

    Item[SQUARE] = {0, 0, 100, 100};
    Item[HEART] = {0, 100, 100, 100};
    Item[CIRCLE] = {100, 0, 100, 100};
    Item[DIAMOND] = {100, 100, 100, 100};
}

void Item::itemRender(int ind, int x, int y, int w, int h, SDL_Renderer* gRenderer){
    SDL_Rect renderSpace = { x, y, w, h};

    SDL_RenderCopy(gRenderer, loadItem, &Item[ind], &renderSpace);
    DelItem();
}
