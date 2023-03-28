#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 430
#define MAX_HEIGHT 250

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 2
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define SLOW_FRAME_CHAR 4
#define SLOW_FRAME_ENEMY 4

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const string IMAGE = "start.png";
const string WINDOW_TITLE = "mo anh lennn";

const int COMMON_BUTTON_WIDTH = 100;
const int COMMON_BUTTON_HEIGHT = 100;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTTON_POSX = 750;
const int PLAY_BUTTON_POSY= 100;
const int HELP_BUTTON_POSX = 750;
const int HELP_BUTTON_POSY = 250;
const int EXIT_BUTTON_POSX = 750;
const int EXIT_BUTTON_POSY = 400;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(std::string msg, int error_code = SDL_ERROR);


#endif // GAME_BASE_H
