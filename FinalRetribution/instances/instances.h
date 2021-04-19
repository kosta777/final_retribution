#ifndef CONSTRUCTORS_H_INCLUDED
#define CONSTRUCTORS_H_INCLUDED

#include "../defines.h"
#include "../game/handlers.h"
#include "../game/campaign.h"

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

// konstruktori
void initTextures();
void initGame(int, char*, int);
void initText(textPtr*, int, int, int, int, int, int, TTF_Font*, char*);
void editText(textPtr*, char*);
void initPlayer();
void initEnemy(double, double, int, int);
void initEffect(double, double, int);
void initBullet(double, double, short, int);
void initPowerUp(double, double, int);

// destruktori
void freeGame();
void freeText(textPtr*);
void freePlayerNode(playerListNodePtr);
void freeEnemyNode(enemyListNodePtr);
void freeEffectNode(effectListNodePtr);
void freeBulletNode(bulletListNodePtr);
void freePowerUpNode(powerUpListNodePtr);

void initLoad_curr_lvl();
void initLevelMatrix();
void saveHighScore();

#endif // CONSTRUCTORS_H_INCLUDED
