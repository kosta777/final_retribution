#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <dirent.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define GAME_NAME "1945: The Final Retribution"

#define WINDOWH 720
#define WINDOWW 1280
#define TOP_STRIP 50
#define BOTTOM_STRIP 50
#define BACKGROUND_SPEED 2

#define initAudio 0
#ifdef WIN32
#define initAudio 1
#endif // WIN32

#define FPS_INTENDED 100
#ifdef WIN32
#define FPS_INTENDED 60
#endif // WIN32

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define BACKGROUNDS_NUM 9
#define BACKGROUND_GRID_X 4
#define BACKGROUND_GRID_Y 5
#define BACKGROUND_TILE_SIZE MAX(WINDOWH/BACKGROUND_GRID_Y, WINDOWW/BACKGROUND_GRID_X)

#define ENEMY_NUM 7
#define ENEMY_PLANE_TYPES 5

// Deklaracije struktura:

/**
* Struktura instance igraca
*/
typedef struct playerStruct
{
    double x_pos;//!< x koordinata
    double y_pos;//!< y koordinata
    int counter; //!< brojač po frejmovima
    int bulletCoolDown; //!< cooldown ispaljivanja metka
    int bombCoolDown; //!< cooldown ispaljivanja bombe
    int health; //!< trenutni health igrača
    int movement; //!< strana na koju se igrač kreće (0:sredina, -1:levo, 1:desno)
    short shieldActive; //!<flag da li je aktivan štit
    short speedActive; //!< flag da li je aktivno ubrzanje
    SDL_Rect position; //!< pravougaonik iscrtavanja
    SDL_Rect texturePosition; //!< pozicija teksture
    void (*handleIteration)(playerListNodePtr); //!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *playerPtr;

/**
* Struktura člana liste igraca
*/
typedef struct playerListNodeStruct
{
    playerPtr player; //!< pokazivač na strukturu igrača
    struct playerListNodeStruct *next;//!< sledeći element liste
    struct playerListNodeStruct *prev;//!< prethodni element liste
} *playerListNodePtr;

/**
* Struktura instance neprijatelja, id {0:obican neprijatelj, 1:dupli health, 2:follower, 3:meta , 4:kamikaze}
*/
typedef struct enemyStruct
{
    double x_pos;//!< x koordinata
    double y_pos;//!< y koordinata
    int counter;//!< brojač po frejmovima
    int coolDown; //!< cooldown ispaljivanja metka
    int id;//!< identifikacioni broj tipa neprijatelja (0:obican, 1:avion sa više health-a, 2:boss follower, 3:kamikaza, 4:glavni boss, 5:meta)
    int path_id;//!< identifikacioni broj putanje po kojoj neprijatelj treba da se kreće
    int texture_slot;//!< textura koja treba da se iscrtava za neprijatelja
    int health;//!< trenutni health neprijatelja
    int score;//!< vrednost neprijatelja u poenima
    SDL_Rect position;//!< pravougaonik iscrtavanja
    SDL_Rect texturePosition;//!< pozicija teksture
    void (*handleIteration)(enemyListNodePtr); //!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *enemyPtr;

/**
* Struktura clana liste neprijatelja
*/
typedef struct enemyListNodeStruct
{
    enemyPtr enemy; //!< pokazivač na strukturu neprijatelja
    struct enemyListNodeStruct *next;//!< sledeći element liste
    struct enemyListNodeStruct *prev;//!< prethodni element liste
} *enemyListNodePtr;

/**
* Struktura instance metka
*/
typedef struct bulletStruct
{
    double x_pos;//!< x koordinata
    double y_pos;//!< y koordinata
    int counter;//!< brojač po frejmovima
    int id; //!< identifikacioni broj tipa metka (1:običan 2:bomba)
    short isPlayerOwned; //!<flag da li je igrač vlasnik metka
    SDL_Rect position;//!< pravougaonik iscrtavanja
    SDL_Rect texturePosition;//!< pozicija teksture
    void (*handleIteration)(bulletListNodePtr); //!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *bulletPtr;

/**
* Struktura člana liste metaka
*/
typedef struct bulletListNodeStruct
{
    bulletPtr bullet;//!< pokazivač na strukturu metka
    struct bulletListNodeStruct *next;//!< sledeći element liste
    struct bulletListNodeStruct *prev;//!< prethodni element liste
} *bulletListNodePtr;


/**
* Struktura instance efekta
*/
typedef struct effectStruct
{
    double x_pos;//!< x koordinata
    double y_pos;//!< y koordinata
    SDL_Rect position;//!< pravougaonik iscrtavanja
    int counter;//!< brojač frejmova od inicijalizacije
    int id;//!< identifikacioni broj tipa efekta (1:dim 2:eksplozija u vazduhu, 3:eksplozija na zemlji, 4:rupa na zemlji, 5:pad običnog aviona, 6:pad štuke, 7:pad bossa followera, 8:pad kamikaza, 9:pad glavnog bossa, 10:štit, 11:brzina)
    int (*handleIteration)(effectListNodePtr); //!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *effectPtr;

/**
* Struktura člana liste efekata
*/
typedef struct effectListNodeStruct
{
    effectPtr effect;//!< pokazivač na strukturu efekta
    struct effectListNodeStruct *next;//!< sledeći element liste
    struct effectListNodeStruct *prev;//!< prethodni element liste
} *effectListNodePtr;

/**
* Struktura instance powerUp-a
*/
typedef struct powerUpStruct
{
    double x_pos;//!< x koordinata
    double y_pos;//!< y koordinata
    SDL_Rect position;//!< pravougaonik iscrtavanja
    int counter;//!< brojač frejmova od inicijalizacije
    int id;//!< identifikacioni broj tipa powerUp-a (1:štit 2:brzina)
    int (*handleIteration)(powerUpListNodeStruct);  //!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *powerUpPtr;

/**
* Struktura clana liste powerUp-a
*/
typedef struct powerUpListNodeStruct
{
    powerUpPtr powerUp;//!< pokazivač na strukturu powerUp-a
    struct powerUpListNodeStruct *next;//!< sledeći element liste
    struct powerUpListNodeStruct *prev;//!< prethodni element liste
} *powerUpListNodePtr;

/**
* Struktura instance koja omogucava ispis teksta
*/
typedef struct textStruct
{
    SDL_Rect rect;//!< pravougaonik iscrtavanja
    SDL_Color color;//!< boja teksta
    char str[5000];//!< tekst
    int show; //!< flag da li da se prikazuje tekst
    TTF_Font *font;//!< font
    SDL_Texture *texture;//!< tekstura koja se iscrtava
} *textPtr;

/**
* Struktura instance igre
*/
typedef struct gameStruct
{
    playerListNodePtr players;//!< pokazivač na aktivne igrače
    enemyListNodePtr enemies;//!< pokazivač na aktivne neprijatelje
    effectListNodePtr effects;//!< pokazivač na aktivne efekte
    bulletListNodePtr bullets;//!< pokazivač na aktivne metke
    powerUpListNodePtr powerUps;//!< pokazivač na aktivne powerUp-ove
    int playersCount;//!< broj igrača
    int enemiesCount;//!< broj neprijatelja
    int effectsCount;//!< broj efekata
    int bulletsCount;//!< broj metkova
    int score;//!< trenutni broj poena igrača
    int frames;//!< broj frejmova
    int framesFromCont;//!< broj frejmova od menija
    int game_mode;//!< aktivan tip igre
    int difficulty; //!< težina igre (0:demo, 1:laka, 2:normalna, 3:teška)
    short boss_active;//!< flag da li je boss aktivan
    short final_boss_active;//!< flag da li je glavni boss aktivan
    int enemySpawnCounter;//!< broj stovernih običnih neprijatelja
    SDL_Texture *explosion_texture;//!< pokazivač na teksturu eksplozije
    SDL_Texture *bullet_texture;//!< pokazivač na teksturu metka
    SDL_Texture *bomb_texture;//!< pokazivač na teksturu bombe
    SDL_Texture *fumes_texture;//!< pokazivač na teksturu dima
    SDL_Texture *holeTexture;//!< pokazivač na teksturu rupe
    SDL_Texture *powerUpTexture;//!< pokazivač na teksturu powerUp-a
    SDL_Texture *playerTexture;//!< pokazivač na teksturu igrača
    SDL_Texture *playerTextureLeft;//!< pokazivač na teksturu igrača okrenutog ka levo
    SDL_Texture *playerTextureRight;//!< pokazivač na teksturu igrača okrenutog ka desno
    SDL_Texture *pauseTexture;//!< pokazivač na teksturu prikazanu u pauzi
    SDL_Texture *shieldTexture;//!< pokazivač na teksturu štita
    SDL_Texture *speedTexture;//!< pokazivač na teksturu koja označava da igrač ima ubrzanje
    SDL_Surface *pauseSurface;//!< pokazivač na teksturu površine prikazane u pauzi
    FILE * level_file;//!< pokazivač na fajl za ulitavanje
    SDL_Texture **backgroundTiles;//!< matrica delova pozadine
    SDL_Texture **enemy_sprites; //!< teksture neprijatelja
    char HSNames[10][51];//!< imena u HighScores
    char HSFileName[256];//!< ime HighScore fajla
    int HSScores[10];//!< poeni u HighScore tabeli
    int level_matrix[BACKGROUND_GRID_Y][BACKGROUND_GRID_X];//!< matrica nivoa
    int level_default;//!< flag da li je podrazumevan nivo aktivan
    int background_offset;//!< offset pozadine
    int campaign_level_ind; //!< indeks nivoa kampanje
    int campaign_row;//!< red u kampanji
    int (*handleIteration)(void);//!< pokazivač na odgovarajuću funkciju koja se poziva pri svakoj iteraciji
} *gamePtr;

#endif // DEFINES_H_INCLUDED
