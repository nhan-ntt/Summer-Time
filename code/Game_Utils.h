#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_base.h"
#include "Button.h"
#include "LTexture.h"
//#include "Vari_and_Const.h"

bool init();
bool loadMedia();
void close();

int UpdateGameTime(int& time, int& speed);

void printText(int score, int POSX, int POSY, SDL_Color textColor, SDL_Renderer* gRenderer, TTF_Font* gFont);

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick);

void HandleEASYButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick, int& LEVEL);
void HandleMEDIUMButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick, int& LEVEL);
void HandleHARDButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick, int& LEVEL);

void HandleLevelButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& level, Mix_Chunk* gClick);

void HandleRestartButton(SDL_Event* e, Button& RestartButton, bool& quit, bool& Restart, Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
                    Button& HelpButton,	Button& BackButton,
                    LTexture gMenuTexture, LTexture gBackButtonTexture,
                    SDL_Renderer *gRenderer, bool &quit,
                    Mix_Chunk *gClick);


void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);

void HandleHomeButton(SDL_Event* e, Button& HomeButton, bool& menu, bool& play, Mix_Chunk* gClick);



#endif // !GAME_UTILS_H_
