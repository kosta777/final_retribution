#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../defines.h"
#include "../draw.h"
#include "../instances/instances.h"
#include "../game/savingGame.h"

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

#define TEXT_TEXTURE_NUM 24

SDL_Texture *backgroundTexture; //!< Tekstura pozadine u meniju
SDL_Texture *selectorTexture; //!< Tekstura selektora u meniju
SDL_Texture *metalFrameTexture; //!< Tekstura metalnog okvira
SDL_Texture *helpTexture; //!< Tekstura koja sadrži sliku sa savetima
SDL_Texture *logoTexture; //!< Tekstura koja sadrži logo igre
SDL_Texture *backgroundOverlay; //!< Tekstura koja služi da zatamni pozadinu
SDL_Rect selectorRect, selector2Rect, metalFrameRect, logoRect, mainMetalFrameRect, helpRect, helpTipRect;
int selectorPos, selector2Pos, difficulty;
Mix_Music *menuMusic; //!< Muzika u glavnom meniju

textPtr textTextures[TEXT_TEXTURE_NUM]; //!< Niz tekstova za ispis na ekranu

char events[256]; //!< Niz zabeleženih događaja

int showMenu();

#endif // MENU_H_INCLUDED
