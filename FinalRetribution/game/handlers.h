#ifndef HANDLERS_H_INCLUDED
#define HANDLERS_H_INCLUDED

#include "../defines.h"
#include "game.h"
#include "../instances/instances.h"

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

// iz game.h
extern SDL_Rect gameOverRect;
extern SDL_Rect HSBackgroundRect;

int gameItrationHandlerDefault();

int playerIterationHandlerDefault(playerListNodePtr);
int playerIterationHandlerDemo(playerListNodePtr);

int enemyIterationHandlerDefault(enemyListNodePtr);
int enemyIterationHandlerFollower(enemyListNodePtr);
int enemyIterationHandlerKamikaze(enemyListNodePtr);
int enemyIterationHandlerBoss(enemyListNodePtr);
int enemyIterationHandlerGroundTarget(enemyListNodePtr);
int powerUpIterationHandler(powerUpListNodePtr);

int bulletIterationHandlerBullet(bulletListNodePtr);
int bulletIterationHandlerBomb(bulletListNodePtr);

int effectIterationHandlerExhaust(effectListNodePtr);
int effectIterationHandlerAirExplosion(effectListNodePtr);
int effectIterationHandlerLandExplosion(effectListNodePtr);
int effectIterationHandlerHole(effectListNodePtr);
int effectIterationHandlerFallingPlane(effectListNodePtr);
int effectIterationHandlerPowerUp(effectListNodePtr);

#endif // HANDLERS_H_INCLUDED
