#include "draw.h"

/**
* Funkcija za iscrtavanje teksta pomoću strukture za iscrtavanje teksta
*/
void drawText(textPtr textTexture)
{
    if (textTexture->show) SDL_RenderCopy(renderer, textTexture->texture, NULL, &(textTexture->rect));
}

/**
* Funkcija za iscrtavanje igrača
*/
void drawPlayers()
{
    playerListNodePtr curr = game->players;
    while (curr)
    {
        if (curr->player->movement == 1)
            SDL_RenderCopy(renderer, game->playerTextureRight, NULL, &(curr->player->position));
        else if (curr->player->movement == -1)
            SDL_RenderCopy(renderer, game->playerTextureLeft, NULL, &(curr->player->position));
        else
            SDL_RenderCopy(renderer, game->playerTexture, NULL, &(curr->player->position));
        curr = curr->next;
    }
}

/**
* Funkcija za iscrtavanje neprijatelja
*/
void drawEnemies()
{
    enemyListNodePtr curr = game->enemies;
    while (curr)
    {
        if (curr->enemy->id >= ENEMY_PLANE_TYPES)
            SDL_RenderCopy(renderer, game->enemy_sprites[curr->enemy->texture_slot], NULL, &(curr->enemy->position));
        curr = curr->next;
    }
    curr = game->enemies;
    while (curr)
    {
        if (curr->enemy->id < ENEMY_PLANE_TYPES)
            SDL_RenderCopy(renderer, game->enemy_sprites[curr->enemy->texture_slot], NULL, &(curr->enemy->position));
        curr = curr->next;
    }
}

/**
* Funkcija za iscrtavanje efekata
*/
void drawEffects()
{
    effectListNodePtr curr = game->effects;
    while (curr)
    {
        if (curr->effect->id == 4) // rupa
            SDL_RenderCopy(renderer, game->holeTexture, NULL, &(curr->effect->position));
        curr = curr->next;
    }
    curr = game->effects;
    while (curr)
    {
        if (curr->effect->id == 1) // bas je super DIM bas se dobro provoDIM uopste te ne viDIM
            SDL_RenderCopy(renderer, game->fumes_texture, NULL, &(curr->effect->position));
        else if (curr->effect->id > 1 && curr->effect->id < 4) //eksplozija
            SDL_RenderCopy(renderer, game->explosion_texture, NULL, &(curr->effect->position));
        else if (curr->effect->id > 4 && curr->effect->id < 10)
            SDL_RenderCopy(renderer, game->enemy_sprites[(curr->effect->id-5)*3+1], NULL, &(curr->effect->position));
        else if(curr->effect->id == 10)
            SDL_RenderCopy(renderer, game->powerUpTexture, NULL, &(curr->effect->position));
        //else if(curr->effect->id == 11)
        //    SDL_RenderCopy(renderer, game->powerUpTexture, NULL, &(curr->effect->position));
        curr = curr->next;
    }
}

/**
* Funkcija za iscrtavanje metaka
*/
void drawBullets()
{
    bulletListNodePtr curr = game->bullets;
    while (curr)
    {
        if (curr->bullet->id==1)
            SDL_RenderCopy(renderer, game->bullet_texture, NULL, &(curr->bullet->position));
        else
            SDL_RenderCopy(renderer, game->bomb_texture, NULL, &(curr->bullet->position));
        curr = curr->next;
    }
}

/**
* Funkcija za iscrtavanje powerup-ova
*/
void drawPowerUps()
{
    powerUpListNodePtr curr = game->powerUps;
    while (curr)
    {
        if (curr->powerUp->id==1)
            SDL_RenderCopy(renderer, game->shieldTexture, NULL, &(curr->powerUp->position));
        if(curr->powerUp->id==2)
            SDL_RenderCopy(renderer, game->speedTexture, NULL, &(curr->powerUp->position));
        curr = curr->next;
    }
}

/**
* Funkcija za iscrtavanje tile-ova
*/
void drawBackground()
{
    SDL_Rect position;
    int i,j;
    position.h = BACKGROUND_TILE_SIZE;
    position.w = BACKGROUND_TILE_SIZE;
    for (i=0;i<BACKGROUND_GRID_Y;i++)
        for (j=0;j<BACKGROUND_GRID_X;j++)
            {position.y = -BACKGROUND_TILE_SIZE + game->background_offset + i*BACKGROUND_TILE_SIZE, position.x = j*BACKGROUND_TILE_SIZE;
            SDL_RenderCopy(renderer, game->backgroundTiles[game->level_matrix[i][j]], NULL, &(position));}
}
