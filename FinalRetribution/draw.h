#ifndef DRAWTEXT_H_INCLUDED
#define DRAWTEXT_H_INCLUDED

#include "defines.h"
#include "instances/instances.h"

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

void drawText(textPtr);
void drawPlayers();
void drawEnemies();
void drawPowerUps();
void drawEffects();
void drawBullets();
void drawBackground();

#endif // DRAWTEXT_H_INCLUDED
