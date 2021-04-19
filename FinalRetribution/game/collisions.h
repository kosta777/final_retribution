#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "../defines.h"
#include "game.h"
#include "../instances/instances.h"

// globalne promenljive (da li ce biti potrebe za ovim uopste?)
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

void detectCollisions(void);
int detectPlayerEnemyCollision(playerPtr, enemyPtr);
int detectBulletEnemyCollision(bulletPtr, enemyPtr);
int detectBulletPlayerCollision(bulletPtr, playerPtr);
int detectPowerUpPlayerCollision(powerUpPtr, playerPtr);
int detectPowerUpEnemyCollision(powerUpPtr, enemyPtr);
#endif // COLLISIONS_H_INCLUDED
