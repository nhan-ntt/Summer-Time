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
#include <windows.h>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

const string IMAGE = "start.png";
const string WINDOW_TITLE = "Summah Time cua Thanh Nahn";

const int COMMON_BUTTON_WIDTH = 180;
const int COMMON_BUTTON_HEIGHT = 95;
const int SMALL_BUTTON_WIDTH = 90;
const int SMALL_BUTTON_HEIGHT = 85;

const int PLAY_BUTTON_POSX = 410;
const int PLAY_BUTTON_POSY= 40;
const int HELP_BUTTON_POSX = 645;
const int HELP_BUTTON_POSY = 40;
const int EXIT_BUTTON_POSX = 270;
const int EXIT_BUTTON_POSY = 40;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;
const int QUIT_BUTTON_POSX = 50;
const int QUIT_BUTTON_POSY = 40;
const int RE_BUTTON_POSX = 165;
const int RE_BUTTON_POSY = 300;

const int LEVEL_POSX = 430;
const int EASY_BUTTON_POSY = 150;
const int MEDIUM_BUTTON_POSY = 270;
const int HARD_BUTTON_POSY = 390;


const int SCORE_POSX = 250;
const int SCORE_POSY = 190;

const int MOVE_POSX = 277;
const int MOVE_POSY = 57;

const int TAR_POSX = 50;
const int TAR_POSY = 190;

const int NumCOL = 9;
const int NumROW = 9;
const int NumItem = 4;
const int itemLength = 60;
const int startX = 420;
const int startY = 30;
const int itemSpeed = 5;
const int timeSleep = 100;
const int moveAllowed[3] = {10, 15, 20};
const int maxScore[3] = {100, 350, 500};

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};
enum Level
{
	EASY, MEDIUM, HARD
};
enum GameItem
{
    BLANK = -1,
    COCONUT, PINEAPPLE, WATERMELON, ORANGE,
    QUAD_VERT, QUAD_HORI,
    QUINTUPLE
};

void LogError(std::string msg, int error_code = SDL_ERROR);


#endif // GAME_BASE_H
