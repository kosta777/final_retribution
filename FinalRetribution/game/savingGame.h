#ifndef SAVINGGAME_H_INCLUDED
#define SAVINGGAME_H_INCLUDED

#include "../defines.h"
#include "game.h"

typedef struct saveHeaderStruct
{
    int enemyNum, bulletNum, effectNum, powerUpNum;
} *saveHeaderPtr;

// globalne promenljive
extern SDL_Rect backgroundRect;
extern SDL_Rect topStripRect, bottomStripRect;
extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern TTF_Font *font;
extern gamePtr game;
extern int lastCampaignLevel;
extern Mix_Music *bgSound;
extern Mix_Chunk *fire;
extern Mix_Chunk *explosionSound;
extern int audio;

void saveGame(char*);
void loadGame(char*);

#endif // SAVEINGGAME_H_INCLUDED
