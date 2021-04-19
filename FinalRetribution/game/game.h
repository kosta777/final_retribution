#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "campaign.h"
#include "../defines.h"
#include "../draw.h"
#include "../instances/instances.h"
#include "collisions.h"

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

#define TEXTS_NUM 15
#define PLAYERS_NUM 1

/**
* Strukrura koja se koristi prilikom snimanja nivoa do kog je predjena kampanja
*/
typedef struct maxLevelSaveStruct
{
    double level; //!< Nivo koji je potrebno zapamtiti
} *maxLevelSavePtr;

/**
* Strukrura koja se koristi prilikom snimanja datoteke sa najboljim rezultatima
*/
typedef struct HSFileMemberStruct
{
    char name[256]; //!< Ime igrača
    int score; //!< Rezultat koji je igrač ostvario
} *HSFileMemberPtr;

SDL_Texture *backgroundTexture;
SDL_Texture *gameOverTexture; //!< Tekstura koja se prikazuje nakon izgubljene partije
SDL_Texture *levelClearTexture; //!< Tekstura koja se prikazuje nakon predjenog nivoa
SDL_Texture *HSBackgroundTexture; //!< Tekstura za pozadinu high score liste
SDL_Rect gameOverRect, HSBackgroundRect;

textPtr texts[TEXTS_NUM]; //!< Niz struktura za ispist teksta
playerPtr players[PLAYERS_NUM]; //!< Niz pokazivača na igrače

char events[256]; //!< Niz zabeleženih događaja sa tastature

void renderGame(void);
void runGame(void);

#endif // GAME_H_INCLUDED
