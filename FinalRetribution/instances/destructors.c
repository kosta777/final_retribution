#include "instances.h"

/**
* Funkcija za deinicijalizaciju strukture igre
* - zovu se destruktori igrača, neprijatelja, efekata i powerUp-ova
* - oslobadjaju se zapamćene teksture i zatvaraju otvoreni fajlovi
*/
void freeGame()
{
    int i;
    if (!game) return;
    while (game->players)
        freePlayerNode(game->players);
    while (game->enemies)
        freeEnemyNode(game->enemies);
    while (game->effects)
        freeEffectNode(game->effects);
    while (game->powerUps)
        freePowerUpNode(game->powerUps);
    for (i=0; i<3*ENEMY_NUM; i++)
        SDL_DestroyTexture(game->enemy_sprites[i]);
    SDL_DestroyTexture(game->fumes_texture);
    SDL_DestroyTexture(game->explosion_texture);
    SDL_DestroyTexture(game->bullet_texture);
    SDL_DestroyTexture(game->bomb_texture);
    SDL_DestroyTexture(game->pauseTexture);
    SDL_DestroyTexture(game->playerTexture);
    SDL_DestroyTexture(game->holeTexture);
    SDL_FreeSurface(game->pauseSurface);
    for (i=0; i<BACKGROUNDS_NUM; i++)
        SDL_DestroyTexture(game->backgroundTiles[i]);
    free(game->backgroundTiles);
    if (game->game_mode==2)
        fclose(game->level_file);
    game = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture za prikaz teksta
* @param    textTexture    Pokazivač na element liste textura koji treba osloboditi
*/
void freeText(textPtr *textTexture)
{
    SDL_DestroyTexture((*textTexture)->texture);
    free(*textTexture);
    textTexture = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture igraca
* - funckija korektno oslobadja memoriju koju prosleđen argument zauzima i prevezuje dvostruko ulančanu listu
* @param    playerNode    Pokazivač na element liste igrača koji treba osloboditi
*/
void freePlayerNode(playerListNodePtr playerNode)
{
    int isMain = playerNode == game->players;
    playerListNodePtr next = playerNode->next, prev = playerNode->prev;
    if(prev!= NULL)
        prev->next = next;
    if(next != NULL)
        next->prev = prev;
    free(playerNode->player);
    free(playerNode);
    if(isMain)
        game->players = next;
    else
        playerNode = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture neprijatelja
* - funckija korektno oslobadja memoriju koju prosleđen argument zauzima i prevezuje dvostruko ulančanu listu
* @param    enemyNode    Pokazivač na element liste neprijatelja koji treba osloboditi
*/
void freeEnemyNode(enemyListNodePtr enemyNode)
{
    int isMain = enemyNode == game->enemies;
    enemyListNodePtr next = enemyNode->next, prev = enemyNode->prev;
    if(prev!= NULL)
        prev->next = next;
    if(next != NULL)
        next->prev = prev;

    if(enemyNode->enemy->id==0)
        game->enemySpawnCounter-=1;

    free(enemyNode->enemy);
    free(enemyNode);
    if(isMain)
        game->enemies = next;
    else
        enemyNode = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture efekta
* - funckija korektno oslobadja memoriju koju prosleđen argument zauzima i prevezuje dvostruko ulančanu listu
* @param    effectNode    Pokazivač na element liste efekata koji treba osloboditi
*/
void freeEffectNode(effectListNodePtr effectNode)
{
    int isMain = effectNode == game->effects;
    effectListNodePtr next = effectNode->next, prev = effectNode->prev;
    if(prev!= NULL)
        prev->next = next;
    if(next != NULL)
        next->prev = prev;
    free(effectNode->effect);
    free(effectNode);
    if(isMain)
        game->effects = next;
    else
        effectNode = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture metka
* - funckija korektno oslobadja memoriju koju prosleđen argument zauzima i prevezuje dvostruko ulančanu listu
* @param    bulletNode    Pokazivač na element liste metaka koji treba osloboditi
*/
void freeBulletNode(bulletListNodePtr bulletNode)
{
    int isMain = bulletNode == game->bullets;
    bulletListNodePtr next = bulletNode->next, prev = bulletNode->prev;
    if(prev!= NULL)
        prev->next = next;
    if(next != NULL)
        next->prev = prev;
    free(bulletNode->bullet);
    free(bulletNode);
    if(isMain)
        game->bullets = next;
    else
        bulletNode = NULL;
}

/**
* Funkcija za deinicijalizaciju strukture powerUp-a
* - funckija korektno oslobadja memoriju koju prosleđen argument zauzima i prevezuje dvostruko ulančanu listu
* @param    powerUpNode    Pokazivač na element liste powerUp-ova koji treba osloboditi
*/
void freePowerUpNode(powerUpListNodePtr powerUpNode)
{
    int isMain = powerUpNode == game->powerUps;
    powerUpListNodePtr next = powerUpNode->next, prev = powerUpNode->prev;
    if(prev!= NULL)
        prev->next = next;
    if(next != NULL)
        next->prev = prev;
    free(powerUpNode->powerUp);
    free(powerUpNode);
    if(isMain)
        game->powerUps = next;
    else
        powerUpNode = NULL;
}
