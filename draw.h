#ifndef DRAW.H
#define DRAW.H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

//start up SDL and create window
bool init();

//load media
bool loadMedia();

//free media and shut down SDL
void close();

//load individual image as texture
SDL_Texture* loadTexture(string path);

//void LogError(string msg, int error_code){
//	if (error_code == SDL_ERROR)
//	{
//		std::cout << msg << SDL_GetError() << std::endl;
//	}
//	if (error_code == IMG_ERROR)
//	{
//		std::cout << msg << IMG_GetError() << std::endl;
//	}
//	if (error_code == MIX_ERROR)
//	{
//		std::cout << msg << Mix_GetError() << std::endl;
//	}
//	if (error_code == TTF_ERROR)
//	{
//		std::cout << msg << TTF_GetError() << std::endl;
//	}
//}

#endif // DRAW
