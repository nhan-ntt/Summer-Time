#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_base.h"
#include "Button.h"
#include "LTexture.h"

bool init();
bool loadMedia();
void close();

void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play, Mix_Chunk* gClick);

void HandlePlayButtonnnn(SDL_Event* e, Button& PlayButton,
                         LTexture gInstructionTexture,
                         bool& QuitMenu, bool& Play,
                         Mix_Chunk* gClick,
                         SDL_Renderer *gRenderer);

void HandleHelpButton(SDL_Event* e, SDL_Rect(&gBackButton)[BUTTON_TOTAL],
                    Button& HelpButton, Button& BackButton,
                    LTexture gInstructionTexture, LTexture gBackButtonTexture,
                    SDL_Renderer *gRenderer,
                    bool &Quit_game, Mix_Chunk *gClick);
void HandleExitButton(SDL_Event* e, Button& ExitButton, bool& Quit, Mix_Chunk* gClick);



#endif // !GAME_UTILS_H_
