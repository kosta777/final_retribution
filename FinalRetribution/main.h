#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "defines.h"
#include "instances/instances.h"
#include "game/handlers.h"
#include "game/collisions.h"

#include "game/game.h"
#include "menu/menu.h"

// globalne promenljive (inicijalizuju se u main, tako da nisu definisane kao extern)
SDL_Rect backgroundRect; //!< Pokazivač na pravougaonik u koji se iscrtava pozadina
SDL_Rect topStripRect; //!< Pokazivač na pravougaonik u koji se iscrtava gornji bar u igri
SDL_Rect bottomStripRect; //!< Pokazivač na pravougaonik u koji se iscrtava donji bar
SDL_Renderer *renderer; //!< Globalni pokazivač na SDL renderer
SDL_Window *window; //!< Globalni pokazivač na SDL window
TTF_Font *font; //!< Globalni pokazivač na SDL font
gamePtr game; //!< Globalni pokazivač na trenutnu započetu ili pauziranu igru
int lastCampaignLevel; //!< Indeks nivoa do koga je pređena igra
Mix_Music *bgSound; //!< Zvuk motora aviona
Mix_Chunk *fire; //!< Zvuk pucnja
Mix_Chunk *explosionSound; //!< Zvuk eksplozije
int audio; //!< Označava da li je zvuk uspoešno inicijalizovan

#endif // MAIN_H_INCLUDED
